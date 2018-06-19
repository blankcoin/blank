// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x27;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x48;
        pchMessageStart[3] = 0x63;
        vAlertPubKey = ParseHex("040bd5d0698b75493d07987b48076a38ef1024bef7c0e0b512c35e45bbfca976ae655e83439cf91bccc34921968ad2022a127ff90e7986506c83716e5c7fbdc631");
        nDefaultPort = 51555;
        nRPCPort = 51556;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "17 June 2018 - BLANKCOIN RELEASE";
        std::vector<CTxIn> vin;
        std::vector<CTxOut> vout;
        vin.resize(1);
        vout.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        vout[0].nValue = 5000;
        vout[0].scriptPubKey = CScript() << ParseHex("0483b2115785c858e40c37a7513b14e2b23afd2cd32b4730f7602cec4e80bfe344c1b7897bdc97cdd3ff3fb44851b7d4d58128256bca181bc5a0194938387f3b23") << OP_CHECKSIG;
        CTransaction txNew(1, 1529232359, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1529232359;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 293707;

        /*// start
        if (true && genesis.GetHash() != hashGenesisBlock)
        {
            //LogPrintf("Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;

            while (true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                {
                    LogPrintf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    LogPrintf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            LogPrintf("genesis.nTime = %u \n", genesis.nTime);
            LogPrintf("genesis.nNonce = %u \n", genesis.nNonce);
            LogPrintf("genesis.nVersion = %u \n", genesis.nVersion);
            LogPrintf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
            LogPrintf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root

        }

        // end */

        hashGenesisBlock = genesis.GetHash();
        //LogPrintf("113 hash = %s \n", hashGenesisBlock.ToString());
        //LogPrintf("114 merkle = %s\n",genesis.hashMerkleRoot.ToString());
        assert(hashGenesisBlock == uint256("0x0000036f4e73eda08265f7f5ae698d675518ac084d1bc7a357ec5da3e9a76134"));
        assert(genesis.hashMerkleRoot == uint256("0x66f7f386315d59c8ee5fbc5946cd4f7ae5fdb840d88c84b55638acad76f9e2f8"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 135); // s
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 49); // K
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

	vFixedSeeds.clear();
        vSeeds.clear();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 0x7fffffff;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xeb;
        pchMessageStart[1] = 0x23;
        pchMessageStart[2] = 0x1d;
        pchMessageStart[3] = 0x42;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04a2a8b02ad14cdb98f0db4ff2b956514993ec5961c304acc85e519d95e2453320b67991bced2b6eadf6996b9c36dffec6b21f090bb548500e881c9d0b87d3f7da");
        nDefaultPort = 55155;
        nRPCPort = 55156;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 757804;



        hashGenesisBlock = genesis.GetHash();
	//LogPrintf("\n 164 genesis.nNonce = %u \n", genesis.nNonce);
        //LogPrintf("\n 164 hashgenesisblock =======  %s \n", hashGenesisBlock.ToString());
	
        assert(hashGenesisBlock == uint256("0xc4076633a17e8e4cc533356536720032d97df61409a4e8efbc2bc30af327fe02"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 125); // s
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 107); // k
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x44;
        pchMessageStart[1] = 0x15;
        pchMessageStart[2] = 0xad;
        pchMessageStart[3] = 0x32;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1528612811;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 446013;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51555;
        strDataDir = "regtest";

        //LogPrintf("\n203 hash %s \n", hashGenesisBlock.ToString());
        assert(hashGenesisBlock == uint256("0x68edaf632baafaaac8a2c042a1cb511fbadcdd483a8febed88bf6bef2f3d7a7f"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
