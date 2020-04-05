#include<iostream>
#include<string>
#include<curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string get_data(const char *get_url){
  CURL *curl = curl_easy_init();
  CURLcode res;
  std::string readBuffer;
  //std::string url = "https://api.covid19india.org/data.json";
  curl_easy_setopt(curl, CURLOPT_URL, get_url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  return readBuffer;
}

std::string remove_quote(std::string s) {
    return s.substr(0, s.size());
}

void india_tallydata(json data){
  std::string head="Covid-19 Count of India";
  for(int i=0;i<30;i++)
    std::cout<<"-";
  std::cout<<'\n';
  std::cout<<head<<"\n";
  for(int i=0;i<30;i++)
    std::cout<<"-";
  std::cout<<'\n';
  std::cout<<"Confirmed : "<<remove_quote(data["confirmed"])<<"\n";
  std::cout<<"Recovered : "<<remove_quote(data["recovered"])<<"\n";
  std::cout<<"Deaths : "<<remove_quote(data["deaths"])<<"\n";
  //std::cout<<"Last Updated On : "<<remove_quote(data["lastupdatedtime"])<<"\n";
}

void print_testeddata(json data){
  std::cout<<"Total Tested : "<<remove_quote(data["totalsamplestested"])<<"\n";
}

void global_tallydata(json data){
  std::string head = "Global Covid-19 Count";
  for(int i=0;i<30;i++)
    std::cout<<"-";
  std::cout<<'\n';
  std::cout<<head<<"\n";
  for(int i=0;i<30;i++)
    std::cout<<"-";
  std::cout<<'\n';
  std::cout<<"Confirmed : "<<data["confirmed"]<<"\n";
  std::cout<<"Recovered : "<<data["recovered"]<<"\n";
  std::cout<<"Deaths : "<<data["deaths"]<<"\n";
}

int main(){
  //std::string global_url="https://covidapi.info/api/v1/global";
  std::string global_url="https://corona-api.com/timeline";
  std::string india_url = "https://api.covid19india.org/data.json";
  json response_global = json::parse(get_data(global_url.c_str()));
  json response_india = json::parse(get_data(india_url.c_str()));
  global_tallydata(response_global["data"][0]);
  india_tallydata(response_india["statewise"][0]);
  print_testeddata(response_india["tested"].back());
  return 0;
}
