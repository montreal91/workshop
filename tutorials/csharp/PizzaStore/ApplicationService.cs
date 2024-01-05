using PizzaStore.Models;

namespace PizzaStore;

public class ApplicationService(IPizzaRepository pizzaRepository, PizzaDb db) {
  public List<Pizza> GetAllPizzas() {
    return pizzaRepository.GetAllPizzas();
  }

  public IResult AddNewPizza(Pizza newPizza) {
    var savedPizza = pizzaRepository.SavePizza(newPizza);
    db.SaveChanges();
    return Results.Created($"/pizzas/{savedPizza.Id}", savedPizza);
  }

  public IResult DeletePizza(int id) {
    var pizza = pizzaRepository.GetPizzaById(id);
    if (pizza is null) {
      return Results.NotFound();
    }

    pizzaRepository.DeletePizza(pizza);
    db.SaveChanges();
    return Results.Ok();
  }

  public IResult UpdatePizza(Pizza updatePizza, int id) {
    var pizza = pizzaRepository.GetPizzaById(id);
    if (pizza is null) {
      return Results.NotFound();
    }

    pizza.Name = updatePizza.Name;
    pizza.Description = updatePizza.Description;

    // pizzaRepository.SavePizza(pizza);
    db.SaveChangesAsync();
    return Results.Ok();
  }
}
