using System.ComponentModel.DataAnnotations;
using Microsoft.EntityFrameworkCore;

namespace PizzaStore.Models {
public class PizzaStore {
  public int Id { get; init; }
  
  [MaxLength(100)]
  public string? Name { get; set; }
  
  [MaxLength(1000)]
  public string? Description { get; set; }
}

internal class PizzaDb(DbContextOptions options) : DbContext(options) {
  public DbSet<PizzaStore> Pizzas { get; init; } = null!;
}
} // namespace PizzaStore.Models