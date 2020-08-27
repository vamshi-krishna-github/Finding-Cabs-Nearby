#include <iostream>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define pi 3.14159265358979323846
#define earth_radius 6371.0

ifstream ipfile("cabdriverdetails.txt");
ofstream opfile("result.txt");

class project
{
public:
    string str;
    long long int punc, colon, x, y, m, n, phone[10000], len;
    long long int i=0;
    char lat_as_string[1000], lon_as_string[1000], phone_as_string[10000], name[10000];
    double lat_cab, lon_cab;

    double degtorad(double deg)
    {
        return (deg * pi / 180);
    }
    double great_circle_distance(double lat_cus, double lon_cus)
    {
        double lat_cus_rad, lon_cus_rad, lat_cab_rad, lon_cab_rad, del_lon, central_angle;

        lat_cus_rad = degtorad(lat_cus);
        lon_cus_rad = degtorad(lon_cus);
        lat_cab_rad = degtorad(lat_cab);
        lon_cab_rad = degtorad(lon_cab);
        del_lon = lon_cab_rad - lon_cus_rad;

        central_angle = acos( sin(lat_cus_rad)*sin(lat_cab_rad) + cos(lat_cus_rad)*cos(lat_cab_rad)*cos(del_lon) );
        return (earth_radius * central_angle);
    }
    void checking(double lat_cus, double lon_cus)
    {
        if(great_circle_distance(lat_cus, lon_cus)<=50.00000)
        {
            phone[i++] = atoll(phone_as_string);
            opfile << "Name: "<<name<<" , Phone Number: "<<phone[i-1]<<endl;
        }

    }
    void validation(double lat_cus, double lon_cus)
    {
        if(ipfile)
        {
            while(getline(ipfile, str))
            {
                punc=0, colon=0, x=0, y=0, m=0, n=0,
                len = str.size();

                for(int j=0;j<len;j++)
                {
                    if(str[j]=='"')
                        punc++;
                    else if(str[j]==':')
                        colon++;

                    if(punc==3)
                    {
                        j++;
                        while(str[j]!='"')
                        {
                            lat_as_string[x++] = str[j++];
                        }
                        j--;
                        lat_as_string[x]='\0';
                    }
                    else if(punc==13)
                    {
                        j++;
                        while(str[j]!='"')
                        {
                            lon_as_string[y++] = str[j++];
                        }
                        lon_as_string[y]='\0';
                        j--;
                    }

                    if(colon==2)
                    {
                        j+=2;
                        while(str[j]!=',')
                        {
                            phone_as_string[m++]=str[j++];
                        }
                        phone_as_string[m]='\0';
                        j--;
                        colon++;
                    }
                    else if(colon==4)
                    {
                        j+=2;
                        while(str[j]!=',')
                        {
                            name[n++]=str[j++];
                        }
                        name[n]='\0';
                        colon++;
                        punc+=2;
                    }
                }

                lat_cab=atof(lat_as_string);
                lon_cab=atof(lon_as_string);
                checking(lat_cus, lon_cus);
            }
        }

        ipfile.close();
        opfile.close();
    }
};

int main()
{
    double lat_cus, lon_cus;
    cout<<"Enter latitude: ";
    cin>>lat_cus;
    cout<<"Enter longitude: ";
    cin>>lon_cus;
    project obj;
    obj.validation(lat_cus, lon_cus);
    return 0;
}
