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

# Initialize Chrome options
chrome_options = Options()
chrome_options.add_experimental_option("detach", True)

# Start the WebDriver
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
input1.send_keys("04/05/2024")

input2 = driver.find_element(By.CSS_SELECTOR, 'input#todate')
input2.send_keys("16/06/2024")

# Submit the form
submit_button = driver.find_element(By.XPATH, '/html/body/form/strong/p[2]/input')
submit_button.click()

# Optionally, wait to observe the result before quitting
sleep(5)

data = []

while True:
    try:
        table = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.XPATH, "/html/body/table[2]")))

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

                    pdf_data = ""
                    txt_data = ""

                    # Download the PDF and extract text
                    if Date_pdf_link:
                        try:
                            response = requests.get(Date_pdf_link)
                            local_pdf = "judgement.pdf"
                            with open(local_pdf, 'wb') as f:
                                f.write(response.content)
                            pdf_document = fitz.open(local_pdf)
                            for page_num in range(pdf_document.page_count):
                                page = pdf_document.load_page(page_num)
                                pdf_data += page.get_text("text")
                            pdf_document.close()
                        except Exception as e:
                            print(f"Failed to process PDF: {e}")

                    # Download the text file and read content
                    if Date_txt_link:
                        try:
                            response = requests.get(Date_txt_link)
                            local_txt = "judgement.txt"
                            with open(local_txt, 'wb') as f:
                                f.write(response.content)
                            with open(local_txt, 'r') as f:
                                txt_data = f.read()
                        except Exception as e:
                            print(f"Failed to process TXT: {e}")

                    data.append([SNo, Case_No, Case_Code, pdf_data, txt_data, Party, Corrigendum])
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

# Create a DataFrame using Pandas
df = pd.DataFrame(data, columns=["SNo", "Case No.", "Case Code", "PDF Data", "TXT Data", "Party", "Corrigendum"])
# Print the DataFrame
print(df)
df.to_csv('Scrap_data.csv', index=False)
driver.quit()
