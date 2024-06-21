from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import requests
import fitz  # PyMuPDF
import pandas as pd
from time import sleep


from datetime import datetime, timedelta

# Define the start and end dates for the 20-year period
start_date = datetime.strptime("1990-12-01", "%Y-%m-%d")
end_date = start_date + timedelta(days=365 * 33)  # 20 years

while start_date < end_date:
    input1_date = start_date.strftime("%d/%m/%Y")
    input2_date = (start_date + timedelta(days=60)).strftime("%d/%m/%Y")

    # Your existing code to interact with the website and extract data for the given two-month period
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
    input1 = driver.find_element(By.XPATH, '/html/body/form/strong/p[1]/input[1]')
    input1.send_keys(start_date.strftime("%d/%m/%Y"))
    
    input2 = driver.find_element(By.CSS_SELECTOR, 'input#todate')
    input2.send_keys(end_date.strftime("%d/%m/%Y"))
    
    # Submit the form
    submit_button = driver.find_element(By.XPATH, '/html/body/form/strong/p[2]/input')
    submit_button.click()
    
    # Optionally, wait to observe the result before quitting
    sleep(5)
    
    data = []
    # Append the extracted data to the 'data' list
    while True:
        try:
            table = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.XPATH, "/html/body/table[2]  ")))

            # Get all rows from the table
            rows = table.find_elements(By.TAG_NAME, "tr")

            # Loop through the rows and extract data
            for row in rows[1:-1]:  # Skipping the header and footer rows
                cells = row.find_elements(By.TAG_NAME, "td")
                if len(cells) > 1:
                    if "deleted" in row.text.lower():  # Check if the row contains the word "deleted"
                        print(f"Skipped deleted row: {row.text}")
                        continue
                    try:
                        SNo = cells[0].text
                        Case_No = cells[1].text.split('\n')[0]
                        Case_Code = cells[1].text.split('\n')[1]
                        Date_pdf_link = cells[2].find_elements(By.TAG_NAME, "a")[0].get_attribute('href')
                        Date_txt_link = cells[2].find_elements(By.TAG_NAME, "a")[1].get_attribute('href')
                        Party = cells[3].text
                        Corrigendum = cells[4].text
                        data.append([SNo, Case_No, Case_Code, Date_pdf_link, Date_txt_link, Party, Corrigendum])
                    except IndexError:
                        print(f"Skipped row due to missing elements: {row.text}")
                    except Exception as e:
                        print(f"An error occurred while processing the row: {e}")
                else:
                    print(f"Skipped row due to insufficient cells: {row.text}")

            # Check if the "Next" button is available and clickable
            next_buttons = driver.find_elements(By.XPATH, '/html/body/table[1]/tbody/tr[2]/td[2]/b/a')
            if next_buttons:
                next_button = None
                for button in next_buttons:
                    if button.text == "Next":
                        next_button = button
                        break
                if next_button:
                    next_button.click()
                    sleep(2)  # Optionally, wait for the next page to load
                else:
                    print("No 'Next' button found. Exiting loop.")
                    break
            else:
                print("No 'Next' buttons found. Exiting loop.")
                break

        except Exception as e:
            print(f"An error occurred: {e}")
            break

        start_date += timedelta(days=60)  # Move to the next two-month period

# Create a DataFrame using Pandas
df = pd.DataFrame(data, columns=["SNo", "Case No.", "Case Code", "Date (pdf)", "Date (txt)", "Party",  "Corrigendum"])
# Print the DataFrame
print(df)
df.to_csv('Scrap_data.csv', mode='a', index=False)  # Append to the existing CSV file
driver.quit()

