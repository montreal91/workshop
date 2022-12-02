package com.example.grpc

import io.grpc.ServerBuilder

fun main() {
    val server = ServerBuilder.forPort(8080)
        .addService(KotlinServiceImpl())
        .build()

    println("Starting 'Hello Kotlin' gRPC server.")
    server.start()
    server.awaitTermination()
}
