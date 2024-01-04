using Microsoft.EntityFrameworkCore;
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

app.MapGet(
  "/pizzas", async (PizzaDb db) => await db.Pizzas.ToListAsync()
);

app.MapPost(
  "/pizzas",
  async (PizzaDb db, PizzaStore.Models.PizzaStore pizza) => {
    await db.Pizzas.AddAsync(pizza);
    await db.SaveChangesAsync();
    return Results.Created($"/pizzas/{pizza.Id}", pizza);
  }
);

app.MapPut(
  "/pizzas/{id:int}",
  async (PizzaStore.Models.PizzaStore updatePizza, PizzaDb db, int id) => {
    var pizza = await db.Pizzas.FindAsync(id);
    if (pizza is null) {
      return Results.NotFound();
    }

    pizza.Name = updatePizza.Name;
    pizza.Description = updatePizza.Description;
    await db.SaveChangesAsync();
    return Results.NoContent();
  }
);

app.MapDelete("/pizzas/{id:int}", async (PizzaDb db, int id) => {
  var pizza = await db.Pizzas.FindAsync(id);
  if (pizza is null) {
    return Results.NotFound();
  }

  db.Pizzas.Remove(pizza);
  await db.SaveChangesAsync();
  return Results.Ok();
});

app.Run();