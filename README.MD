    # xml2pdf
     
      This is a simple command-line tool that provides functionality to transform XML files into HTML using XSLT and to convert HTML files into PDF.
     
      ## Installation
     
      ### Linux
      
       #### Prerequisites
       - libxml2 (development files)
       - libxslt (development files)
       - wkhtmltopdf
      
       #### Install libxml2 and libxslt
       ```sh
       sudo apt-get update
       sudo apt-get install libxml2-dev libxslt-dev
       ```
      
       #### Install wkhtmltopdf
       ```sh
       sudo apt-get install wkhtmltopdf
       ```
      
       ### macOS
      
       #### Prerequisites
       - libxml2 (development files)
       - libxslt (development files)
       - wkhtmltopdf
      
       #### Install libxml2 and libxslt
       ```sh
       brew install libxml2 libxslt
       ```
      
       #### Install wkhtmltopdf
       ```sh
       brew install --cask wkhtmltopdf
       ```
      
       ## Usage
      
       To transform an XML file to HTML:
       ```sh
       ./xml2pdf --xml2html <xml_file> <xslt_file> <output_html_file>
       ```
      
       To convert an HTML file to PDF:
       ```sh
       ./xml2pdf --html2pdf <html_file> <output_pdf_file>
       ```
      
       ## Command-Line Options
      
       - `--xml2html`: Transform XML to HTML using XSLT
       - `--html2pdf`: Convert HTML to PDF
       - `--help`: Print usage information
      
       ## Build Instructions
      
       1. Clone the repository:
       ```sh
       git clone https://github.com/<username>/xml2pdf.git
       ```
      
       2. Navigate to the project directory:
       ```sh
       cd xml2pdf
       ```
      
       3. Compile the source code using CMake:
       ```sh
       mkdir build && cd build
       cmake ..
       make
       ```
      
       4. Run the executable:
       ```sh
       ./xml2pdf
       ```
      
       ## License
      
       This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.