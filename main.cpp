#include "mbed.h"
#include <string>
#include "OLEDDisplay.h"
#include "http_request.h"
#include "MbedJSONValue.h"
#include "src/shared/PrintUtils.cpp"
#include "src/service/HttpService.cpp"

/*
    0 = stoldo
    1 = sitri
    2 = school
*/
#define PROFILE 0

#if defined(PROFILE) && PROFILE == 0
    #define WIFI_SSID "eny-98710"
    #define WIFI_PASSWORD "y32t-fcy8-mjxw-s6mp"
#endif

#if defined(PROFILE) && PROFILE == 1
    #define WIFI_SSID "TODO"
    #define WIFI_PASSWORD "TODO"
#endif

#if defined(PROFILE) && PROFILE == 2
    #define WIFI_SSID "LERNKUBE"
    #define WIFI_PASSWORD "l3rnk4b3"
#endif


OLEDDisplay oled(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL);
DigitalOut myled(MBED_CONF_IOTKIT_LED1);

int main() {
    PrintUtils::print("Profile: ", PROFILE);

    oled.clear();    
    oled.printf("Sunrise Sunset\n");

    HttpService httpService(WIFI_SSID, WIFI_PASSWORD);

    while( 1 )
    {
        myled = 1;
        // By default the body is automatically parsed and stored in a buffer, this is memory heavy.
        // To receive chunked response, pass in a callback as last parameter to the constructor.
        HttpRequest* get_req = new HttpRequest(httpService.getValueTmp(), HTTP_GET, "http://api.sunrise-sunset.org/json?lat=47.3686498&lng=8.5391825");

        HttpResponse* get_res = get_req->send();
        // OK
        if ( get_res )
        {
            MbedJSONValue parser;
            // HTTP GET (JSON) parsen  
            parse( parser, get_res->get_body_as_string().c_str() );
            
            std::string sunrise;
            std::string sunset;
            
            sunrise = parser["results"]["sunrise"].get<std::string>();
            sunset  = parser["results"]["sunset"] .get<std::string>(); 
            
            // Umwandlung nach int. Damit die Zeiten besser verglichen werden können.
            int rh, rm, rs, sh, sm, ss;
            sscanf( sunrise.c_str(), "%d:%d:%d AM", &rh, &rm, &rs );
            sscanf( sunset .c_str(), "%d:%d:%d PM", &sh, &sm, &ss );
            
            oled.cursor( 1, 0 );
            oled.printf( "auf   %02d.%02d.%02d\nunter %02d.%02d.%02d\n", rh+2, rm, rs, sh+2+12, sm, ss );
        }
        // Error
        else
        {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return 1;
        }
        delete get_req;
        myled = 0;

        thread_sleep_for( 10000 );
    }
}
