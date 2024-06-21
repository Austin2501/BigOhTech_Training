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

data = []

# Create a CSV file and write header
with open('Scrap_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["SNo", "Case No.", "Case Code", "Date (pdf)", "Date (txt)", "Party", "Corrigendum"])

# Define the start and end dates for the 5-year period
start_date = datetime.strptime("1990-12-01", "%Y-%m-%d")
end_date = start_date + timedelta(days=365 * 20)  # 34 years

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
