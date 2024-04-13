#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxslt/xslt.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

typedef struct {
    const char *name;
    const char *description;
    int (*execute)(int argc, char **argv);
} command;

int transform_xml_to_html(int argc, char **argv);
int convert_html_to_pdf(int argc, char **argv);
int print_usage(int argc, char **argv);

command commands[] = {
        {"--xml2html", "Transform XML to HTML using XSLT", transform_xml_to_html},
        {"--html2pdf", "Convert HTML to PDF", convert_html_to_pdf},
        {"--help", "Print usage information", print_usage},
        {NULL, NULL, NULL}
};

/**
 * Transform XML to HTML using XSLT
 *
 * This function takes three command line arguments: the path to the XML file,
 * the path to the XSLT file, and the path to the output HTML file. It loads
 * the XML file, parses it, parses the XSLT file, applies the XSLT transformation
 * to the XML document, and outputs the result as HTML to the specified file.
 *
 * @param argc The number of command line arguments
 * @param argv An array of command line argument strings
 * @return 1 if the number of command line arguments is less than 4, otherwise 0
 */
int transform_xml_to_html(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <xml file> <xslt file> <output html file>\n", argv[0]);
        return 1;
    }
    const char *xml_file = argv[1];
    const char *xslt_file = argv[2];
    const char *html_file = argv[3];

    xmlDocPtr doc, res;
    xsltStylesheetPtr cur;

    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;

    doc = xmlParseFile(xml_file);
    cur = xsltParseStylesheetFile((const xmlChar *)xslt_file);
    res = xsltApplyStylesheet(cur, doc, NULL);

    FILE *output = fopen(html_file, "w");
    xsltSaveResultToFile(output, res, cur);
    fclose(output);

    xsltFreeStylesheet(cur);
    xmlFreeDoc(res);
    xmlFreeDoc(doc);

    xsltCleanupGlobals();
    xmlCleanupParser();

    printf("HTML generated successfully.\n");
    return 0;
}


/**
 * @brief Converts an HTML file to a PDF file using wkhtmltopdf command-line tool.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 *
 * @return 0 if the PDF is generated successfully, 1 otherwise.
 *
 * @note The command must be executed with three arguments: the name of the HTML file to convert,
 *       and the path of the output PDF file.
 * @note The wkhtmltopdf command-line tool must be installed on the system for this function to work.
 */
int convert_html_to_pdf(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <html_file_path> <output_pdf_file_path>\n", argv[0]);
        return 1;
    }

    char command[1000];
    sprintf(command, "wkhtmltopdf %s %s", argv[1], argv[2]);

    int status = system(command);

    if (status == 0) {
        printf("PDF generated successfully.\n");
        return 0;
    } else {
        fprintf(stderr, "Error generating PDF.\n");
        return 1;
    }
}

int print_usage(int argc, char **argv) {
    printf("Usage: %s <command> [arguments]\n", argv[0]);
    printf("Commands:\n");
    for (int i = 0; commands[i].name != NULL; i++) {
        printf("%s: %s\n", commands[i].name, commands[i].description);
    }
    return 0;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        print_usage(argc, argv);
        return 1;
    }

    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(argv[1], commands[i].name) == 0) {
            return commands[i].execute(argc - 1, argv + 1);
        }
    }

    fprintf(stderr, "Unknown command '%s'. Use --help for usage information.\n", argv[1]);
    return 1;
}
