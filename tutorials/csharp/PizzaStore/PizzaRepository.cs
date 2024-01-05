using PizzaStore.Models;

namespace PizzaStore;

public interface IPizzaRepository {
  public Pizza? GetPizzaById(int id);
  public List<Pizza> GetAllPizzas();
  public Pizza SavePizza(Pizza pizza);
  public void DeletePizza(Pizza pizza);
}

public class PizzaRepository(PizzaDb db) : IPizzaRepository {
  public Pizza? GetPizzaById(int id) {
    return db.Pizzas.Find(id);
  }

  public List<Pizza> GetAllPizzas() {
    return db.Pizzas.ToList();
  }

  public Pizza SavePizza(Pizza pizza) {
    db.Pizzas.Add(pizza);
    return pizza;
  }

  public void DeletePizza(Pizza pizza) {
    db.Pizzas.Remove(pizza);
  }
}
