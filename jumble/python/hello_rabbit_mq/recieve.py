
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(host="localhost"))
channel = connection.channel()

channel.queue_declare(queue="hello")

def callback(ch, method, properties, body):
    print("[x] Recieved {message}".format(message=body))

channel.basic_consume(callback, queue="hello", no_ack=True)

channel.start_consuming()
