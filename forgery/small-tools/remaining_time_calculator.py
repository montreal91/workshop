from datetime import datetime

def get_remaining_time(big_date):
    dt = big_date - big_date.now()
    hours = dt.days * 24 + dt.seconds // 3600
    minutes = (dt.seconds // 60) % 60
    print("Remaining time:")
    print("{0:d} hours, {1:d} minutes".format(hours, minutes))


early_return = datetime(year=2017, month=11, day=21, hour=11)
late_return = datetime(year=2017, month=11, day=21, hour=19)

print("Early:")
get_remaining_time(early_return)

print("\nLate:")
get_remaining_time(late_return)

midnight = datetime(year=2017, month=11, day=19, hour=0)
get_remaining_time(midnight)
