using Xunit;

using Prime.Services;

namespace Prime.Unittests.Services;

public class PrimeService_IsPrimeShould {
    [Theory]
    [InlineData(-1)]
    [InlineData(0)]
    [InlineData(1)]
    public void Test1(int value) {
        var primeService = new PrimeService();
        bool result = primeService.IsPrime(value);

        Assert.False(result, $"{value} should not be prime");
    }
}
