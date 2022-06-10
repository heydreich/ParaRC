#ifndef _ECTASK_HH_
#define _ECTASK_HH_

#include "../inc/include.hh"
#include "../util/RedisUtil.hh"
#include "../protocol/AGCommand.hh"

using namespace std;

/*
 * Type of ECTasks
 * 0: read from disk and cache locally
 * 1: fetch from several remote nodes, perform computation locally (if any), and cache result locally
 * 2: fetch from several remote nodes, concactenate them and persist to disk
 */

//class ComputeTask {
//  public:
//    vector<int> _srclist;
//    vector<int> _dstlist;
//    vector<vector<int>> _coefs;
//  
//    ComputeTask(vector<int> srclist, vector<int> dstlist, vector<vector<int>> coefs) {
//      _srclist = srclist;
//      _dstlist = dstlist;
//      _coefs = coefs;
//    }
//};

class ECTask {

  private:
    int _type; 
    unsigned int _loc;

    // for type 0
    string _blockName;
    int _blkBytes;
    int _pktBytes;
    int _ecw; // sub-packetization
    unordered_map<int, int> _cid2refs;
    string _stripeName;

    // for type 1
    vector<int> _prevIndices;
    vector<unsigned int> _prevLocs;
    vector<ComputeTask*> _computeTaskList;
    // stripeName
    vector<int> _indices;
    // _ecw
    // _blkBytes
    // _pktBytes

    // for type 2
    //_prevIndices;
    //_prevLocs;
    //_stripeName
    // _blockName

  public:
    ECTask();
    ~ECTask();

//    void buildReadDisk(int type, 
//               unsigned int loc,
//               string blockname,
//               int ecw,
//               vector<int> indices,
//               string stripename); 
    void buildReadDisk(int type,
            unsigned int loc,
            string blockname,
            int blkbytes,
            int pktbytes,
            int ecw,
            unordered_map<int, int> cid2ref,
            string stripename);
    void buildFetchCompute(int type,
               unsigned int loc,
               vector<int> prevIndices,
               vector<unsigned> prevLocs,
               vector<ComputeTask*> computelist,
               string stripename,
               vector<int> indices,
               int ecw, int blkbytes, int pktbytes);
    void buildConcatenate(int type,
               unsigned int loc,
               vector<int> prevIndices,
               vector<unsigned int> prevLocs,
               string stripename,
               string blockname,
               int ecw, int blkbytes, int pktbytes);

    int getType();
    vector<ComputeTask*> getComputeTaskList();
    string dumpStr();
    AGCommand* genAGCommand();
};

#endif
