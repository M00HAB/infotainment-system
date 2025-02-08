from datetime import datetime

def get_date_time():
    now = datetime.now()
    current_date = now.strftime("%Y-%m-%d")  # Store date in YYYY-MM-DD format
    current_time = now.strftime("%H:%M:%S")  # Store time in HH:MM:SS format
    return current_date, current_time

date, time = get_date_time()

print("Date:", date)
print("Time:", time)
