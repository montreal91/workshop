using Microsoft.OpenApi.Models;
using PizzaStore;
using PizzaStore.Models;

var builder = WebApplication.CreateBuilder(args);

var connectionString = builder.Configuration.GetConnectionString("Pizzas") ?? "Data Source=Pizzas.db";

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c => {
  c.SwaggerDoc("v1",
    new OpenApiInfo {
      Title = "PizzaStore API",
      Description = "Making the Pizzas you love",
      Version = "v1"
    });
});

builder.Services.AddScoped<IMyDependency, MyDependencyImpl>();
builder.Services.AddScoped<IMyService, MyServiceImpl>();
builder.Services.AddSqlite<PizzaDb>(connectionString);
builder.Services.AddScoped<IPizzaRepository, PizzaRepository>();
builder.Services.AddScoped<ApplicationService>();

var app = builder.Build();

app.UseSwagger();
app.UseSwaggerUI(c => { c.SwaggerEndpoint("/swagger/v1/swagger.json", "PizzaStore API V1"); });

var counter = 0;

app.MapGet("/", (IMyService service) => {
  var res = $"Hello World! {counter}";
  counter++;
  return service.DoStuff(res);
});

var multiCounter = 0;

app.MapGet("/{num:int}", (int num, IMyService service) => {
  var res = $"Hello DotNet! {multiCounter}";
  multiCounter += num;
  return service.DoStuff(res);
});

app.MapGet(
  "/pizzas/{id:int}",
  async (PizzaDb db, int id) => await db.Pizzas.FindAsync(id)
);

app.MapGet("/pizzas", (ApplicationService aps) => aps.GetAllPizzas());

app.MapPost(
  "/pizzas",
  (ApplicationService service, Pizza pizza) => service.AddNewPizza(pizza)
);

app.MapPut(
  "/pizzas/{id:int}",
  (ApplicationService service, Pizza updatePizza, int id) => service.UpdatePizza(updatePizza, id)
);

app.MapDelete(
  "/pizzas/{id:int}",
  (ApplicationService service, int id) => service.DeletePizza(id)
);

app.Run();
