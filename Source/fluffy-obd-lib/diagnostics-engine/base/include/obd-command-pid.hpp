#ifndef OBD_COMMAND_PID_HPP_
#define OBD_COMMAND_PID_HPP_

// clang-format off
enum class ObdCommandPid
{
    //Service 01 Show current data
    S01P00, S01P01, S01P02, S01P03, S01P04, S01P05, S01P06, S01P07,
    S01P08, S01P09, S01P0A, S01P0B, S01P0C, S01P0D, S01P0E, S01P0F,

    S01P10, S01P11, S01P12, S01P13, S01P14, S01P15, S01P16, S01P17,
    S01P18, S01P19, S01P1A, S01P1B, S01P1C, S01P1D, S01P1E, S01P1F,

    S01P20, S01P21, S01P22, S01P23, S01P24, S01P25, S01P26, S01P27,
    S01P28, S01P29, S01P2A, S01P2B, S01P2C, S01P2D, S01P2E, S01P2F,

    S01P30, S01P31, S01P32, S01P33, S01P34, S01P35, S01P36, S01P37,
    S01P38, S01P39, S01P3A, S01P3B, S01P3C, S01P3D, S01P3E, S01P3F,

    //Service 02 Show freeze frame data
    S02P00, S02P01, S02P02, S02P03, S02P04, S02P05, S02P06, S02P07,
    S02P08, S02P09, S02P0A, S02P0B, S02P0C, S02P0D, S02P0E, S02P0F,

    S02P10, S02P11, S02P12, S02P13, S02P14, S02P15, S02P16, S02P17,
    S02P18, S02P19, S02P1A, S02P1B, S02P1C, S02P1D, S02P1E, S02P1F,

    S02P20, S02P21, S02P22, S02P23, S02P24, S02P25, S02P26, S02P27,
    S02P28, S02P29, S02P2A, S02P2B, S02P2C, S02P2D, S02P2E, S02P2F,

    S02P30, S02P31, S02P32, S02P33, S02P34, S02P35, S02P36, S02P37,
    S02P38, S02P39, S02P3A, S02P3B, S02P3C, S02P3D, S02P3E, S02P3F,

    //Service 03 Show stored Diagnostic Trouble Codes
    S03,

    //Service 04 Clear Diagnostic Trouble Codes and stored values
    S04,

    //Service 05 Test results, oxygen sensor monitoring
    S05P0100,
    S05P0101, S05P0102, S05P0103, S05P0104, S05P0105, S05P0106, S05P0107, S05P0108,
    S05P0109, S05P010A, S05P010B, S05P010C, S05P010D, S05P010E, S05P010F, S05P0110,

    S05P0201, S05P0202, S05P0203, S05P0204, S05P0205, S05P0206, S05P0207, S05P0208,
    S05P0209, S05P020A, S05P020B, S05P020C, S05P020D, S05P020E, S05P020F, S05P0210,

    //Service 07 Show pending Diagnostic Trouble Codes
    S07,

    //Service 09 Request vehicle information
    S09P00, S09P01, S09P02, S09P03, S09P04, S09P05, S09P06, S09P07,
    S09P08, S09P09, S09P0A, S09P0B,

    //Service 0A Permanent Diagnostic Trouble Codes
    S0A
};
// clang-format on

#endif // OBD_COMMAND_PID_HPP_