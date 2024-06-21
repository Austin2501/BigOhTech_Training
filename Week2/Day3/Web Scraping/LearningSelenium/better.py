from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import pandas as pd
from time import sleep

n = int(input("Enter no. of datasets: "))
i = 0;

while(n>0):
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

    # Print the page source for debugging (optional)
    print(driver.page_source)

    start = input("Input start date: ")
    # Locate and interact with the input elements inside the frame
    input1 = driver.find_element(By.XPATH, '/html/body/form/strong/p[1]/input[1]')
    input1.send_keys(start)

    end = input("Input end date: ")
    input2 = driver.find_element(By.CSS_SELECTOR, 'input#todate')
    input2.send_keys(end)

    # Submit the form
    submit_button = driver.find_element(By.XPATH, '/html/body/form/strong/p[2]/input')
    submit_button.click()

    # wait to observe the result before quitting
    sleep(5)

    table = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.XPATH, "/html/body/table[2]")))

    # Get all rows from the table
    rows = table.find_elements(By.TAG_NAME, "tr")

    # Initialize an empty list to store the data
    data = []

    # Loop through the rows and extract data
    for row in rows[1:-1]:  # Skipping the header and footer rows
        cells = row.find_elements(By.TAG_NAME, "td")
        if len(cells) > 1:
            SNo = cells[0].text
            Case_No = cells[1].text.split('\n')[0]
            Case_Code = cells[1].text.split('\n')[1]
            Date_pdf_link = cells[2].find_elements(By.TAG_NAME, "a")[0].get_attribute('href')
            Date_txt_link = cells[2].find_elements(By.TAG_NAME, "a")[1].get_attribute('href')
            Party = cells[3].text
            Corrigendum = cells[4].text
            data.append([SNo, Case_No, Case_Code, Date_pdf_link, Date_txt_link, Party, Corrigendum])

    # Create a DataFrame using Pandas
    df = pd.DataFrame(data, columns=["SNo", "Case No.", "Case Code", "Date (pdf)", "Date (txt)", "Party",   "Corrigendum"])

    # Print the DataFrame
    print(df)
    
    
    count = str(i+1)
    name = "Scrap" + count + ".csv"

    df.to_csv(f'Week2/Day3/Web Scraping/{name}', index=False)
    n = n-1
driver.quit()

