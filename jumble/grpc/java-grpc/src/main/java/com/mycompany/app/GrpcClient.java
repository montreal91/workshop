package com.mycompany.app;

import com.mycompany.app.grpc.HelloRequest;
import com.mycompany.app.grpc.HelloResponse;
import com.mycompany.app.grpc.HelloServiceGrpc;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;

public class GrpcClient {
  public static void main(String[] args) {
    ManagedChannel channel = ManagedChannelBuilder.forAddress("localhost", 8080)
                                                  .usePlaintext()
                                                  .build();

    HelloServiceGrpc.HelloServiceBlockingStub stub = HelloServiceGrpc.newBlockingStub(channel);
    HelloResponse helloResponse = stub.hello(
        HelloRequest.newBuilder()
                    .setFirstName("Quirinus")
                    .setLastName("Quirrell")
                    .build()
    );
    channel.shutdown();

    System.out.println("Got gRPC response: " + helloResponse.getGreeting());
  }
}
