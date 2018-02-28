
import time

from celery import Celery
from flask_socketio import emit

from app import socketio
from app import make_celery
from config import broker_url

# from server import my_app


# celery = make_celery(my_app)

# @celery.task
# def countdown(n):
#     print(n)

#     for i in range(n+1):
#         time.sleep(1)
#         print("Socket", socketio)
#         print("Server", socketio.server)
#         socketio.emit(
#             "countdown",
#             {"remaining": n - i},
#             namespace="/test/"
#         )
