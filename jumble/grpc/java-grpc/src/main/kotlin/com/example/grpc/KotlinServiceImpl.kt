package com.example.grpc

import com.mycompany.app.grpc.HelloRequest
import com.mycompany.app.grpc.HelloResponse
import com.mycompany.app.grpc.HelloServiceGrpc.HelloServiceImplBase
import io.grpc.stub.StreamObserver

class KotlinServiceImpl : HelloServiceImplBase() {
    override fun hello(
            request: HelloRequest?,
            responseObserver: StreamObserver<HelloResponse>?
    ) {
        println("First name: ${request?.firstName}\nLast name: ${request?.lastName}")
        val response = HelloResponse
                .newBuilder()
                .setGreeting("Hello, ${request?.firstName} ${request?.lastName}!")
                .build()

        responseObserver?.onNext(response)
        responseObserver?.onCompleted()
    }
}
