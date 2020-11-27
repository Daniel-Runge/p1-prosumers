void get_api (char* filemode, char* url, char* filename);
int fileMaker(void);


typedef struct /*Data we get from the API in MW |POWER CONSUMTION STRUCT|*/
{
    double battery_discharge;
    double biomass;
    double coal;
    double gas;
    double hydro;
    double hydro_discharge;
    double nuclear;
    double oil;
    double solar;
    double wind;
    double geothermal;
    double unknown;
} data_consumption;

typedef struct /*Data we get from the API in MW |TOTAL SECTION|*/
{
    double fossile;
    double renewable;
    double consumptionTotal;
    double productionTotal;
    double ImportTotal;
    double ExportTotal;
    double carbon_intensity;
} data_total;

double EnergyParser(char *Filename, char *KeyWord);
void readFile(data_total *POWAH);

int green_power(data_total *value);

void welcomeprint();
void printdata(data_total total, data_consumption consumption, int parameter);