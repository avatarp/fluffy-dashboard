#ifndef DTC_HANDLER_TEST_H_
#define DTC_HANDLER_TEST_H_

#include "elm327-dtc-handler.hpp"

#include <gtest/gtest.h>

class Elm327DtcHandlerTest : public ::testing::Test {
protected:
    Elm327DtcHandler dtcHandler;
    Response response;
};

TEST_F(Elm327DtcHandlerTest, ParseEmptyDtcResponse)
{
    response.raw.commandId = "03";
    response.raw.data = "00";

    EXPECT_NO_THROW(dtcHandler.ParseStoredDtc(response));

    EXPECT_TRUE(dtcHandler.GetStoredDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetPendingDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetPermanentDtcCodes().empty());
}

TEST_F(Elm327DtcHandlerTest, ParseStoredDtcValidResponse)
{
    response.raw.commandId = "03";
    response.raw.data = "013223";

    EXPECT_NO_THROW(dtcHandler.ParseStoredDtc(response));
    auto dtcCodes = dtcHandler.GetStoredDtcCodes();
    EXPECT_EQ(dtcCodes.size(), 1);
    EXPECT_EQ(dtcCodes[0], "P3223");

    EXPECT_TRUE(dtcHandler.GetPendingDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetPermanentDtcCodes().empty());
    dtcHandler.ClearDtcData();
    EXPECT_TRUE(dtcHandler.GetStoredDtcCodes().empty());
}

TEST_F(Elm327DtcHandlerTest, ParsePendingDtcValidResponse)
{
    response.raw.commandId = "07";
    response.raw.data = "0243004700";

    EXPECT_NO_THROW(dtcHandler.ParsePendingDtc(response));
    auto dtcCodes = dtcHandler.GetPendingDtcCodes();
    EXPECT_EQ(dtcCodes.size(), 2);
    EXPECT_EQ(dtcCodes[0], "C0300");
    EXPECT_EQ(dtcCodes[1], "C0700");

    EXPECT_TRUE(dtcHandler.GetStoredDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetPermanentDtcCodes().empty());
    dtcHandler.ClearDtcData();
    EXPECT_TRUE(dtcHandler.GetPendingDtcCodes().empty());
}

TEST_F(Elm327DtcHandlerTest, ParsePermanentDtcValidResponse)
{
    response.raw.commandId = "0A";
    response.raw.data = "04B110C15847003223";

    EXPECT_NO_THROW(dtcHandler.ParsePermanentDtc(response));
    auto dtcCodes = dtcHandler.GetPermanentDtcCodes();
    EXPECT_EQ(dtcCodes.size(), 4);
    EXPECT_EQ(dtcCodes[0], "B3110");
    EXPECT_EQ(dtcCodes[1], "U0158");
    EXPECT_EQ(dtcCodes[2], "C0700");
    EXPECT_EQ(dtcCodes[3], "P3223");
    
    EXPECT_TRUE(dtcHandler.GetPendingDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetStoredDtcCodes().empty());

    dtcHandler.ClearDtcData();
    EXPECT_TRUE(dtcHandler.GetPermanentDtcCodes().empty());
}

TEST_F(Elm327DtcHandlerTest, ParseInvalidCommandId)
{
    response.raw.commandId = "04"; // Invalid command ID

    EXPECT_THROW(dtcHandler.ParseStoredDtc(response), std::runtime_error);
    EXPECT_THROW(dtcHandler.ParsePendingDtc(response), std::runtime_error);
    EXPECT_THROW(dtcHandler.ParsePermanentDtc(response), std::runtime_error);
}

TEST_F(Elm327DtcHandlerTest, ParseInvalidLength)
{
    response.raw.data = "01"; // Invalid length for DTC response

    response.raw.commandId = "03";
    EXPECT_THROW(dtcHandler.ParseStoredDtc(response), std::runtime_error);

    response.raw.commandId = "07";
    EXPECT_THROW(dtcHandler.ParsePendingDtc(response), std::runtime_error);

    response.raw.commandId = "0A";
    EXPECT_THROW(dtcHandler.ParsePermanentDtc(response), std::runtime_error);

    EXPECT_TRUE(dtcHandler.GetStoredDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetPendingDtcCodes().empty());
    EXPECT_TRUE(dtcHandler.GetPermanentDtcCodes().empty());
}

#endif // DTC_HANDLER_TEST_H_