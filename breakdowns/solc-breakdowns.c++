//0x608060405234801561000f575f80fd5b506101438061001d5f395ff3fe608060405234801561000f575f80fd5b5060043610610034575f3560e01c8063cdfead2e14610038578063e026c01714610054575b5f80fd5b610052600480360381019061004d91906100ba565b610072565b005b61005c61007b565b60405161006991906100f4565b60405180910390f35b805f8190555050565b5f8054905090565b5f80fd5b5f819050919050565b61009981610087565b81146100a3575f80fd5b50565b5f813590506100b481610090565b92915050565b5f602082840312156100cf576100ce610083565b5b5f6100dc848285016100a6565b91505092915050565b6100ee81610087565b82525050565b5f6020820190506101075f8301846100e5565b9291505056fea264697066735822122061db4d7d551178866839e41e424bb77c522cc44941025da066b22a96efffde0964736f6c63430008140033

//1. Contract creation code
// Free memory pointer
PUSH1 0x80      // [0x080]
PUSH1 0x40      // [0x40, 0x080]
MSTORE          // []
//------
// If someone sent value with this call revert, otherwise jump to 0x000f jump dest
CALLVALUE       // [msg.value]
DUP1            // [msg.value, msg.value] 
ISZERO          // [msg.value == 0, msg.value] 
PUSH2 0x000f    // [0x000f, msg.value == 0, msg.value]
JUMPI           // [msg.value]
PUSH0           // [0x00, msg.value]
DUP1            // [0x00, 0x00, msg.value]
REVERT          // [msg.value]

// sticks the runtime code on chain
JUMPDEST        // [msg.value]
POP             // []
PUSH2 0x0143    // [0x0143]
DUP1            // [0x0143, 0x0143] 
PUSH2 0x001d    // [0x001d, 0x0143, 0x0143] 
PUSH0           // [0x00, 0x001d, 0x0143, 0x0143] 
CODECOPY        // [0x0143]
PUSH0           // [0x00, 0x0143]
RETURN          // [] halt execution
INVALID         // [] end of contract creation bytecode
// -----------------------------------------------------
// 2. Runtime code
// entry point of all calls
// free memory pointer
PUSH1 0x80
PUSH1 0x40
MSTORE

// checking if msg.value, and if given, reverting
CALLVALUE           // [msg.value]
DUP1                // [msg.value, msg.value]  
ISZERO              // [msg.value == 0, msg.value] 
PUSH2 0x000f        // [0x00f, msg.value == 0, msg.value] 
JUMPI               // [msg.value] // jump to "JUMPDEST 1"
PUSH0               // [0x00, msg.value]
DUP1                // [0x00, 0x00, msg.value] 
REVERT              // [msg.value]

// if msg.value == 0, start here
// "JUMPDEST 1"
// This is checking to see if there is enough calldata for a function selector
JUMPDEST            // [msg.value]
POP                 // []
PUSH1 0x04          // [0x04]
CALLDATASIZE        // [calldata_size, 0x04]
LT                  // [calldata_size < 0x04]
PUSH2 0x0034        // [0x0034, calldata_size < 0x04]
JUMPI               // [] // jump to "JUMPDEST 2" 

// dispatching for updateNumberOfHorses
PUSH0               // [0x00]
CALLDATALOAD        // [32bytes of calldata] 
PUSH1 0xe0          // [0xe0, 32bytes of calldata] 
SHR                 // [calldata[0:4]] func_selector
DUP1                // [func_selector, func_selector]
PUSH4 0xcdfead2e    // [0xcdfead2e, func_selector, func_selector]
EQ                  // [func_selector == 0xcdfead2e, func_selector]
PUSH2 0x0038        // [0x0038, func_selector == 0xcdfead2e, func_selector]
JUMPI               // [func_selector]
// if func_selector == 0xcdfead2e jumpt to update_number_of_horses

// dispatching for readNumberOfHorses
DUP1                // [func_selector, func_selector]
PUSH4 0xe026c017    // [0xe026c017, func_selector, func_selector]
EQ                  // [func_selector == 0xe026c017, func_selector]
PUSH2 0x0054        // [0x0054, func_selector == 0xe026c017, func_selector]
JUMPI               // [func_selector]
// if func_selector == 0xe026c017 jumpt to read_number_of_horses

// "JUMPDEST 2"
// Revert Jumpdest
JUMPDEST             // []
PUSH0                // [0x00]
DUP1                 // [0x00, 0x00]
REVERT               // []


JUMPDEST
PUSH2 0x0052
PUSH1 0x04
DUP1
CALLDATASIZE
SUB
DUP2
ADD
SWAP1
PUSH2 0x004d
SWAP2
SWAP1
PUSH2 0x00ba
JUMP
JUMPDEST
PUSH2 0x0072
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH2 0x005c
PUSH2 0x007b
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
PUSH2 0x0069
SWAP2
SWAP1
PUSH2 0x00f4
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN
JUMPDEST
DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
DUP1
SLOAD
SWAP1
POP
SWAP1
JUMP
JUMPDEST
PUSH0
DUP1
REVERT
JUMPDEST
PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP
JUMPDEST
PUSH2 0x0099
DUP2
PUSH2 0x0087
JUMP
JUMPDEST
DUP2
EQ
PUSH2 0x00a3
JUMPI
PUSH0
DUP1
REVERT
JUMPDEST
POP
JUMP
JUMPDEST
PUSH0
DUP2
CALLDATALOAD
SWAP1
POP
PUSH2 0x00b4
DUP2
PUSH2 0x0090
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
DUP5
SUB
SLT
ISZERO
PUSH2 0x00cf
JUMPI
PUSH2 0x00ce
PUSH2 0x0083
JUMP
JUMPDEST
JUMPDEST
PUSH0
PUSH2 0x00dc
DUP5
DUP3
DUP6
ADD
PUSH2 0x00a6
JUMP
JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH2 0x00ee
DUP2
PUSH2 0x0087
JUMP
JUMPDEST
DUP3
MSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH2 0x0107
PUSH0
DUP4
ADD
DUP5
PUSH2 0x00e5
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
PUSH2 0xdb4d
PUSH30 0x551178866839e41e424bb77c522cc44941025da066b22a96efffde096473
PUSH16 0x6c63430008140033