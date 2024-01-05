using System.ComponentModel.DataAnnotations;
using Microsoft.EntityFrameworkCore;

namespace PizzaStore.Models;

public class Pizza {
  public int Id { get; init; }
  
  [MaxLength(100)]
  public string? Name { get; set; }
  
  [MaxLength(1000)]
  public string? Description { get; set; }
}

public class PizzaDb(DbContextOptions options) : DbContext(options) {
  public DbSet<Pizza> Pizzas { get; init; } = null!;
}
