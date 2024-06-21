from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import csv
from time import sleep
from datetime import datetime, timedelta
from PyPDF2 import PdfReader
import requests
import os
import chardet
from pdf2image import convert_from_path
import pytesseract
import cv2
import numpy as np

# Function to download a file from a URL
def download_file(url, file_path):
    response = requests.get(url)
    with open(file_path, 'wb') as file:
        file.write(response.content)

# Function to extract text from a PDF file
def extract_text_from_pdf(pdf_path):
    text = ""
    try:
        pdf_reader = PdfReader(pdf_path)
        for page in pdf_reader.pages:
            page_text = page.extract_text()
            if page_text:
                text += page_text
            else:
                # Convert PDF page to image and use OCR
                images = convert_from_path(pdf_path, first_page=pdf_reader.pages.index(page) + 1, last_page=pdf_reader.pages.index(page) + 1)
                for image in images:
                    image_np = np.array(image)
                    gray_image = cv2.cvtColor(image_np, cv2.COLOR_BGR2GRAY)
                    ocr_text = pytesseract.image_to_string(gray_image)
                    text += ocr_text
    except Exception as e:
        print(f"An error occurred while extracting text from PDF: {e}")
    return text

# Function to read text from a TXT file
def read_text_from_txt(txt_path):
    text = ""
    try:
        with open(txt_path, 'rb') as txt_file:
            raw_data = txt_file.read()
            result = chardet.detect(raw_data)
            encoding = result['encoding']
            text = raw_data.decode(encoding)
    except Exception as e:
        print(f"An error occurred while reading text from TXT: {e}")
    return text

data = []

# Create a CSV file and write header
with open('Scrap_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["SNo", "Case No.", "Case Code", "Date (pdf)", "Date (txt)", "Party", "Corrigendum", "PDF Text", "TXT Text"])

# Define the start and end dates for the 5-year period
start_date = datetime.strptime("1990-12-01", "%Y-%m-%d")
end_date = start_date + timedelta(days=365 * 2)  # 2 years

# Initialize Chrome options
chrome_options = Options()
chrome_options.add_experimental_option("detach", True)
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=chrome_options)
driver.maximize_window()
driver.get("https://dhccaseinfo.nic.in/jsearch/")

# Click on the input button
input_button = driver.find_element(By.XPATH, '/html/body/table[2]/tbody/tr[1]/td[5]/b/input')
input_button.click()

# Switch to the frame using the embed element
driver.switch_to.frame(driver.find_element(By.CSS_SELECTOR, 'body > embed'))

# Locate and interact with the input elements inside the frame
input1 = driver.find_element(By.XPATH, '//*[@id="frdate"]')
input1.clear()
input1.send_keys(start_date.strftime("%d/%m/%Y"))
input2 = driver.find_element(By.CSS_SELECTOR, 'input#todate')
input2.clear()
input2.send_keys(end_date.strftime("%d/%m/%Y"))
# Submit the form
submit_button = driver.find_element(By.CSS_SELECTOR, '#Submit')
submit_button.click()

# Optionally, wait to observe the result before quitting
sleep(5)

while True:
    try:
        table = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.XPATH, "/html/body/table[2]")))

        # Get all rows from the table
        rows = table.find_elements(By.TAG_NAME, "tr")
        for row in rows[1:-1]:  # Skipping the header and footer rows
            cells = row.find_elements(By.TAG_NAME, "td")
            if len(cells) > 1:
                try:
                    SNo = cells[0].text
                    Case_No = cells[1].text.split('\n')[0] if '\n' in cells[1].text else cells[1].text
                    Case_Code = cells[1].text.split('\n')[1] if '\n' in cells[1].text else 'N/A'
                    Date_pdf_link = cells[2].find_elements(By.TAG_NAME, "a")[0].get_attribute('href') if cells[2].find_elements(By.TAG_NAME, "a") else 'N/A'
                    Date_txt_link = cells[2].find_elements(By.TAG_NAME, "a")[1].get_attribute('href') if len(cells[2].find_elements(By.TAG_NAME, "a")) > 1 else 'N/A'
                    Party = cells[3].text
                    Corrigendum = cells[4].text
                    data.append([SNo, Case_No, Case_Code, Date_pdf_link, Date_txt_link, Party, Corrigendum])
                except Exception as e:
                    print(f"An error occurred while processing the row: {e}")
            else:
                print(f"Skipped row due to insufficient cells: {row.text}")

        # Update the existing code to process PDF and TXT files
        for row in data:
            pdf_text = ""
            txt_text = ""
            if row[3] != 'N/A':
                pdf_path = "temp.pdf"
                download_file(row[3], pdf_path)
                pdf_text = extract_text_from_pdf(pdf_path)
                os.remove(pdf_path)
            
            if row[4] != 'N/A':
                txt_path = "temp.txt"
                download_file(row[4], txt_path)
                txt_text = read_text_from_txt(txt_path)
                os.remove(txt_path)
            
            row.extend([pdf_text, txt_text])

        # Append the data to the CSV file after each page
        with open('Scrap_data.csv', 'a', newline='') as file:
            writer = csv.writer(file)
            for row in data:
                writer.writerow(row)
            data = []  # Clear data after writing

        # Check if the "Next" button is available and clickable
        next_buttons = driver.find_elements(By.XPATH, "/html/body/table[1]/tbody/tr[2]/td[2]/b/a[text()='Next']")
        if next_buttons:
            next_button = next_buttons[0]  # There should only be one "Next" button
            next_button.click()
            sleep(2)  # Wait for the next page to load
        else:
            print("All pages have been processed.")
            break
    except Exception as e:
        print(f"An error occurred while processing the page: {e}")
        break

# Quit the driver
driver.quit()
