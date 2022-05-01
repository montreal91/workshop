using Xunit;
using System;
using Pets;

namespace NewTypesTests;

public class PetTests {
    [Fact]
    public void Test1() {
        Assert.Equal("Woof!", new Dog().TalkToOwner());
        Assert.Equal("Meow!", new Cat().TalkToOwner());
    }
}
