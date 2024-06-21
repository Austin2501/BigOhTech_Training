import requests
import fitz  # PyMuPDF
import pandas as pd

# Define the URL and the local file name
url = "https://dhccaseinfo.nic.in/jsearch/qrcode.php?nc=1992%3ADHC%3A2&ctype=S&cno=927&cyr=1988"
local_pdf = "judgement.pdf"

# Download the PDF
response = requests.get(url)
with open(local_pdf, 'wb') as f:
    f.write(response.content)

# Open the PDF with PyMuPDF
pdf_document = fitz.open(local_pdf)

# Extract text from each page
text_data = []
for page_num in range(pdf_document.page_count):
    page = pdf_document.load_page(page_num)
    text = page.get_text("text")
    text_data.append(text)

# Close the PDF document
pdf_document.close()

# Convert the extracted text into a DataFrame
# Assuming each extracted page text will be in a single row in the CSV
df = pd.DataFrame({'Page Text': text_data})

# Save the DataFrame to a CSV file
csv_file = "judgement_text.csv"
df.to_csv(csv_file, index=False)

print(f"PDF text has been extracted and saved to {csv_file}")
