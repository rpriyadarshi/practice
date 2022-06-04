#pragma once

class intTreeTest : public ::testing::Test {
public: // Using, typedefs etc.
private: // Class data
    nonstd::sample_builder<int> m_sample_builder;

protected:
    void SetUp() override 
    {
        m_sample_builder.build();
    }

    void TearDown() override
    {

    }

public: // Accessors
    const nonstd::sample_builder<int> get_sample_builder() const { return m_sample_builder; }
    nonstd::sample_builder<int> get_sample_builder() { return m_sample_builder; }
};
