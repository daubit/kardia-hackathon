#pragma once

#include "CoreMinimal.h"

/*--------------------RPC-----------------------*/

const FString RPC_ID = "1";
const FString JSON_RPC = "2.0";

/*--------------------Node-----------------------*/

const FString NODE_INFO = "node_nodeInfo";
const FString NODE_PEERS = "node_peers";
const FString NODE_DATADIR = "node_datadir";

/*--------------------Block-----------------------*/

const FString BLOCK_NUMBER = "kai_blockNumber";
const FString BLOCK_BY_HASH = "kai_getBlockByHash";
const FString BLOCK_BY_NUMBER = "kai_getBlockByNumber";
const FString BLOCK_HEADER_BY_HASH = "kai_getBlockHeaderByHash";
const FString BLOCK_HEADER_BY_NUMBER = "kai_getBlockHeaderByNumber";

/*--------------------Chain-----------------------*/

const FString LOGS = "kai_getLogs";
const FString CALL = "kai_kardiaCall";
const FString VALIDATOR = "kai_validator";
const FString VALIDATORS = "kai_validators";
const FString VALIDATOR_SET = "kai_getValidatorSet";

const FString PROOF = "kai_getProof";
const FString COMMIT = "kai_getCommit";

const FString GAS_PRICE = "kai_gasPrice";
const FString ESTIMATE_GAS = "kai_estimateGas";


/*--------------------Filter-----------------------*/

const FString NEW_FILTER = "kai_newFilter";
const FString FILTER_CHANGES = "kai_getFilterChanges";
const FString NEW_BLOCK_FILTER = "kai_newBlockFilter";
const FString UNINSTALL_FILTER = "kai_uninstallFilter";

/*--------------------Transaction-----------------------*/

const FString TX = "tx_getTransaction";
const FString SEND_RAW_TX = "tx_sendRawTransaction";
const FString PENDING_TX = "tx_pendingTransactions";
const FString TX_RECEIPT = "tx_getTransactionReceipt";


/*--------------------Account-----------------------*/

const FString NONCE = "account_nonce";
const FString CODE = "account_getCode";
const FString BALANCE = "account_balance";
const FString STORAGE_AT = "account_getStorageAt";
const FString NONCE_AT_HEIGHT = "account_nonceAtHeight";


