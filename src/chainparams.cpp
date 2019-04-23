// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018      The MTNC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000008bb286c4db1d437bfe799bfa4d8c560f2cde71e52049114aae2b824a44c"));
  //  (1, uint256("0x00000dd955900a094ae8b426b4b0839ec3af15bc8547932618b7152dc570c66d"))
 //   (23600, uint256("0x000000000017713395201d641f820c2cf8c5b066bc1953d8ad5f179d1e8e95d4"))
  //  (23601, uint256("0x69c4fd7cc957dbadadff11f11c26dde96f1e40a9eab48b81618df2c04cad3c39"))
  //  (43216, uint256("0x07317d726d4da7657b9af5c7decd882a96b344d6e3e7cb6ba22322b78c2e3c31"));
    
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1550984444, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1550985444,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1550986444,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xb4;
        vAlertPubKey = ParseHex("0433e1111155e27905052fb0da7521898434ae0fe686852aa9419d67a3dd5996de8aba5738ebad48cd46f6b9541bbf4c086c3d2f344f8d1ec8fc1b5a94248fb37d");
        nDefaultPort = 11186;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // MTNC starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 3240;
        nRejectBlockOutdatedMajority = 4104;
        nToCheckBlockUpgradeMajority = 4320;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // MTNC: 2 minute
        nTargetSpacing = 2 * 60;  // MTNC: 2 minute
        nMaturity = 80;
        nMinStakeAge = 2 * 60 * 60;
        nMasternodeCountDrift = 3;
        nMaxMoneyOut = 120000000 * COIN;

        strPreminePubKey = ParseHex("03ef511112114e7a097a42c30c54d004956f7c78ba1df710702b9a37a46d602168");

        /** Height or Time Based Activations **/
        nLastPOWBlock = 6000;
        nModifierUpdateBlock = 10001;
        nZerocoinStartHeight = 10001;
        nZerocoinStartTime = 1550985444; // 
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = INT_MAX; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = INT_MAX; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = INT_MAX; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = INT_MAX; //Start enforcing the invalid UTXO's

        
		const char* pszTimestamp = "Masternodecoin REBORN 2019";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f231111de09af6a9d93fdc3a570d25abf67871961b1305798b42ab910f9e468c97bbc60cbb17edc9228991fb71f9b13a6229b4843677cf359cf19539d4dd86b2") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1550984444;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 457157;
if(genesis.GetHash() != uint256("0x"))
{
      printf("MSearching for genesis block...\n");
      uint256 hashTarget;
      hashTarget.SetCompact(genesis.nBits);
      while(uint256(genesis.GetHash()) > uint256(hashTarget))
      {
          ++genesis.nNonce;
          if (genesis.nNonce == 0)
          {
              printf("Mainnet NONCE WRAPPED, incrementing time");
              std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
              ++genesis.nTime;
          }
          if (genesis.nNonce % 10000 == 0)
          {
              printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
          }
      }
      printf("Mainnet block.nTime = %u \n", genesis.nTime);
      printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
      printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
      printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
}
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000008bb286c4db1d437bfe799bfa4d8c560f2cde71e52049114aae2b824a44c"));
        assert(genesis.hashMerkleRoot == uint256("0xb16e0185fd60fd42e727a370b072fbc6360b5f908c22de7fc8f52e7a1182c5d1"));

        vSeeds.push_back(CDNSSeedData("seed1", "seed1.masternodecoin.online"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.masternodecoin.vip"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.masternodecoin.pro"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.masternodecoin.site"));
        vSeeds.push_back(CDNSSeedData("seed5", "142.252.250.2"));
        vSeeds.push_back(CDNSSeedData("seed5", "50.118.255.28"));
        vSeeds.push_back(CDNSSeedData("dnsseed", "dnsseed.MTNC.live"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 50);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04f231111de09af6a9d93fdc3a570d25abf67871961b1305798b42ab910f9e468c97bbc60cbb17edc9228991fb71f9b13a6229b4843677cf359cf19539d4dd86b2";
        strObfuscationPoolDummyAddress = "MVbQ5zVe8GJTDXRbhZaNe4KpEcD2cQReB7";
        nStartMasternodePayments = 1550985444; //

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x25;
        pchMessageStart[1] = 0x26;
        pchMessageStart[2] = 0x27;
        pchMessageStart[3] = 0x28;
        vAlertPubKey = ParseHex("0433e1111155e27905052fb0da7521898434ae0fe686852aa9419d67a3dd5996de8aba5738ebad48cd46f6b9541bbf4c086c3d2f344f8d1ec8fc1b5a94248fb37d");
        nDefaultPort = 61474;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // 2min
        nTargetSpacing = 2 * 60;  // 2min
        nLastPOWBlock = 300;
        nMaturity = 10;

        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0; 
        nMaxMoneyOut = 120000000 * COIN;
        nZerocoinStartHeight = 301;
        nZerocoinStartTime = 1550986444; // 1 29, 2019
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = INT_MAX; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = INT_MAX; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = INT_MAX; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = INT_MAX; //Start enforcing the invalid UTXO's

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1550985444;
        genesis.nNonce = 214096;
if(genesis.GetHash() != uint256("0x"))
{
      printf("MSearching for genesis block...\n");
      uint256 hashTarget;
      hashTarget.SetCompact(genesis.nBits);
      while(uint256(genesis.GetHash()) > uint256(hashTarget))
      {
          ++genesis.nNonce;
          if (genesis.nNonce == 0)
          {
              printf("Mainnet NONCE WRAPPED, incrementing time");
              std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
              ++genesis.nTime;
          }
          if (genesis.nNonce % 10000 == 0)
          {
              printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
          }
      }
      printf("Mainnet block.nTime = %u \n", genesis.nTime);
      printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
      printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
      printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
}
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000006547e813776b04c20357b7c3609d53ab4e9ad7e0f3879c550bb37153ee6"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("test-seed1", "test-seed1.MTNC.live"));
        vSeeds.push_back(CDNSSeedData("test-seed2", "test-seed2.MTNC.live"));
        vSeeds.push_back(CDNSSeedData("test-seed3", "test-seed3.MTNC.live"));
        vSeeds.push_back(CDNSSeedData("test-seed4", "test-seed4.MTNC.live"));
        vSeeds.push_back(CDNSSeedData("test-seed5", "50.118.255.28"));
        vSeeds.push_back(CDNSSeedData("test-dnsseed", "test-dnsseed.MTNC.live"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet MTNC addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet MTNC script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet MTNC BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet MTNC BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet MTNC BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04f231111de09af6a9d93fdc3a570d25abf67871961b1305798b42ab910f9e468c97bbc60cbb17edc9228991fb71f9b13a6229b4843677cf359cf19539d4dd86b2";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1550986444; //19 Apr 2018 22:00:00 GMT
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x71;
        pchMessageStart[3] = 0xa2;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 2 * 60; // MTNC: 2 minute
        nTargetSpacing = 2 * 60;  // MTNC: 2 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1550986444;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 61476;
  //      assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 61478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
