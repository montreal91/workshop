namespace Prime.Services;
public class PrimeService {
    public bool IsPrime(int candidate) {
        if (Math.Abs(candidate) == 1) {
            return false;
        }

        if (candidate == 0) {
            return false;
        }

        throw new NotImplementedException("Not implemented");
    }
}
