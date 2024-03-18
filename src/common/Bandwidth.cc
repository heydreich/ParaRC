#include "Bandwidth.hh"

Bandwidth::Bandwidth(std::string& filepath)     {
    XMLDocument doc;
    if(doc.LoadFile(filepath.c_str()) != XML_NO_ERROR)
        std::cerr << "XMLfile incorrect\n";
    XMLElement* element;
    std::unordered_map<int,double> UploadMap;
    std::unordered_map<int,double> DownloadMap;
    for(element = doc.FirstChildElement("setting")->FirstChildElement("attribute");
           element!=NULL;
           element=element->NextSiblingElement("attribute")){
       XMLElement* ele = element->FirstChildElement("name");
       std::string attName = ele -> GetText();
       if (attName == "upload.bandwidth") {
            for (ele = ele -> NextSiblingElement("value"); ele != NULL; ele = ele -> NextSiblingElement("value")) {
                // std::string rack = "default";
                std::string uplinks = ele -> GetText();
                int pos = uplinks.find(":");
                int len = uplinks.length();
                std::string s_uplinkidx = uplinks.substr(0, pos);
                std::string s_upload = uplinks.substr(pos + 1, len - pos - 1);
                int uplinkidx = std::stoi(s_uplinkidx);
                double upload = std::stod(s_upload);
                UploadMap.insert(std::make_pair(uplinkidx, upload));
                // unsigned int ip = inet_addr(ipstr.c_str());
                // _agentsIPs.push_back(ip);
            }
        //    for (int i=0; i<_agentsIPs.size(); i++) {
        //        unsigned int ip = _agentsIPs[i];
        //        _ip2agentid.insert(std::make_pair(ip, i));
        //     }
       } else if (attName == "download.bandwidth"){
            for (ele = ele -> NextSiblingElement("value"); ele != NULL; ele = ele -> NextSiblingElement("value")) {
                // std::string rack = "default";
                std::string downlinks = ele -> GetText();
                int pos = downlinks.find(":");
                int len = downlinks.length();
                std::string s_downlinkidx = downlinks.substr(0, pos);
                std::string s_download = downlinks.substr(pos + 1, len - pos - 1);
                int downlinkidx = std::stoi(s_downlinkidx);
                double download = std::stod(s_download);
                DownloadMap.insert(std::make_pair(downlinkidx, download));
                // unsigned int ip = inet_addr(ipstr.c_str());
                // _agentsIPs.push_back(ip);
            }
       }   
    }
    for (auto it : UploadMap) {
        int Index = it.first;
        _ip2bdwt.insert(std::make_pair(Index, std::make_pair( DownloadMap[Index],UploadMap[Index])));
        // std::cout << Index << ":" << UploadMap[Index] << "," << DownloadMap[Index]<< std::endl;
    }
}

Bandwidth::~Bandwidth() {

}
