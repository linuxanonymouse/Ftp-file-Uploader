#include <stdio.h>
#include <curl/curl.h>
// before runing the app give it the nessary permission to do that by useing this command sduo chmod +x ftp_connect
// to connect and upload file top the ftp server user this command ./ftp_connect "YOUR_IP "USERNAME" "PASSWORD"

int main(int argc, char *argv[]) {
    CURL *curl;
    CURLcode res;
    char ftp_url[100];
    const char *hostname = argv[1];
    const char *username = argv[2];
    const char *password = argv[3];
    // this var is used to upload file to the ftp server so please provide your file that you want to upload here
    const char *upload_file = "hello.txt";
    const char *remote_directory = "/"; 

    snprintf(ftp_url, sizeof(ftp_url), "ftp://%s%s/%s", hostname, remote_directory, upload_file);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a CURL handle
    curl = curl_easy_init();
    if (curl) {
        // Set FTP URL
        curl_easy_setopt(curl, CURLOPT_URL, ftp_url);

        // Provide username and password for FTP authentication
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

        // Set verbose option to get more information
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Set the file to be uploaded
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fopen(upload_file, "rb"));

        // Perform the FTP operation
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup the CURL handle
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}
