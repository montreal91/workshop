
from concurrent import futures
import logging

import grpc
import helloworld_pb2
import helloworld_pb2_grpc


class Greeter(helloworld_pb2_grpc.Greeter):
    def SayHello(self, request, context):
        return helloworld_pb2.HelloReply(message="Hello, %s" % request.name)
