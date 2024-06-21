import requests
import pandas as pd

# Define the URL and the local file name
url = "https://dhccaseinfo.nic.in/jsearch/downloadtext.php?path=dhc/NBK/judgement/15-06-2024/&name=NBK15062024CW84222024_141119.txt"
local_txt = "judgement.txt"

# Download the text file
response = requests.get(url)
with open(local_txt, 'wb') as f:
    f.write(response.content)

# Read the downloaded text file
with open(local_txt, 'r') as f:
    lines = f.readlines()

# Process the text file
# This is a basic example of processing text; you may need to adjust based on the text structure
data = []
for line in lines:
    # Assuming each line represents a row in the CSV file
    # You may need to adjust the parsing logic based on actual text content and desired CSV structure
    row = line.strip().split()  # Split by whitespace
    data.append(row)

# Convert the processed data into a DataFrame
df = pd.DataFrame(data)

# Save the DataFrame to a CSV file
csv_file = "judgement_data.csv"
df.to_csv(csv_file, index=False, header=False)

print(f"Text data has been extracted and saved to {csv_file}")
