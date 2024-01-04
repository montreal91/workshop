namespace PizzaStore {
public interface IMyDependency {
  string MakeMessage(string message);
}

public class MyDependencyImpl : IMyDependency {
  public string MakeMessage(string message) {
    return $"This is my message:'{message}'";
  }
}

public interface IMyService {
  public string DoStuff(string message);
}

public class MyServiceImpl(IMyDependency myDependency) : IMyService {
  public string DoStuff(string message) {
    return myDependency.MakeMessage(message);
  }
}
}