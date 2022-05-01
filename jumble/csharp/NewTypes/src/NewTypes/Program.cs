
using Pets;
using System.Collections.Generic;
using System;

namespace ConsoleApplication;

public class Program {
    public static void Main(string[] args) {
        List<Pet> pets = new List<Pet> {
            new Dog(),
            new Cat()
        };

        foreach (var pet in pets) {
            Console.WriteLine(pet.TalkToOwner());
        }
    }
}
