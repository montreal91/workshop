package com.mycompany.app;

import com.mycompany.app.grpc.HelloRequest;
import com.mycompany.app.grpc.HelloResponse;
import com.mycompany.app.grpc.HelloServiceGrpc;
import io.grpc.stub.StreamObserver;

public class HelloServiceImpl extends HelloServiceGrpc.HelloServiceImplBase {
  @Override
  public void hello(HelloRequest request, StreamObserver<HelloResponse> responseObserver) {
    System.out.println(
        "First name: " +
            request.getFirstName() +
            " Last name: " +
            request.getLastName()
    );

    String greeting = "Hello, " + request.getFirstName() + " " + request.getLastName();
    HelloResponse response = HelloResponse.newBuilder()
                                          .setGreeting(greeting)
                                          .build();

    responseObserver.onNext(response);
    responseObserver.onCompleted();
  }
}
