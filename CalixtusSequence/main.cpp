//
//  main.cpp
//  CalixtusSequence
//
//  Created by Aniket Sedhai on 6/16/24.
//

#include <iostream>
#include <fstream>

/**
 @brief This method generates the calixtus sequence from the 0th item in the calixtus sequence to however many the user desires.
 @param[in] sequence_length - the number of elements in the calixtus sequence that user wants to generate
 @param[out] ret_calixtus_sequence_buffer_p - pointer to the return buffer to store the sequence values
 @param[in] size_of_buffer - size of the buffer needed to store the calixtus sequence
 
 @return 0 on success and non zero on failure.
 */
int get_calixtus_sequence(uint32_t sequence_length, uint32_t* ret_calixtus_sequence_buffer_p, uint32_t size_of_buffer);

/**
 @brief This method creates/opens a file and writes user provided data into it.
 @param[in] data_p - pointer to the array holding the data
 @param[in] data_length - length of data
 @param[in] filepath - path and name of the file
 
 @return 0 on success and non zero on failure.
 */
int generate_txt_file_from_buffer(uint32_t* data_p, uint32_t data_length, std::string filepath);

int main(void)
{
    uint32_t seq_buffer[100];
    uint32_t sequence_length = 100;
    std::string filepath;
    
    std::cout << "Enter the filepath (name included). Use '.txt' extension: " << std::endl;
    std::cin >> filepath;

    /*only print the sequence if the generation of the sequence was successfull*/
    if(get_calixtus_sequence(sequence_length, seq_buffer, sizeof(seq_buffer)/sizeof(uint32_t)) == 0)
    {
        std::cout << "Calixtus sequence: " <<std::endl;
        
        /*print each of the elements in the sequence*/ 
        for (int i = 0; i < sequence_length; i++)
        {
            std::cout << seq_buffer[i] << "\t";
        }
        
        std::cout << std::endl;
        
        generate_txt_file_from_buffer(seq_buffer, sizeof(seq_buffer)/sizeof(uint32_t), filepath);
        
        return 0;
    }
    
    return 0;
}

int get_calixtus_sequence(uint32_t sequence_length, uint32_t* ret_calixtus_sequence_buffer_p, uint32_t size_of_buffer)
{
    uint32_t index = 2;
    uint8_t c_0 = 1;
    uint8_t c_1 = 3;
    
    /*check for NULL parameter*/
    if (ret_calixtus_sequence_buffer_p == NULL)
    {
        std::cout << "Null parameter!!!" << std::endl;
        return 1;
    }
    
    /*ensure that the sequence length is at least 1*/
    if (sequence_length <= 0)
    {
        std::cout << "Invalid sequence length" << std::endl;
        return 1;
    }
    
    /*the buffer size should be atleast as big as the sequence length*/
    if (size_of_buffer < sequence_length)
    {
        std::cout << "Buffer size cannot be smaller than sequence length" << std::endl;
        return 1;
    }
    
    /*define the values in the sequence we already know*/
    *ret_calixtus_sequence_buffer_p = c_0;
    *(ret_calixtus_sequence_buffer_p + 1) = c_1;
    
    
    /*calculate each value in the sequence until the user desired sequence is built up*/
    for (index = 2; index < sequence_length; index++)
    {
        if (index % 3 == 0)
        {
            *(ret_calixtus_sequence_buffer_p + index) = *(ret_calixtus_sequence_buffer_p + index - 1) + *(ret_calixtus_sequence_buffer_p + index - 2);
        }
        else if (index % 2 == 0)
        {
            *(ret_calixtus_sequence_buffer_p + index) = *(ret_calixtus_sequence_buffer_p + index - 1)/2;
        }
        else
        {
            *(ret_calixtus_sequence_buffer_p + index) = index;
        }
    }
    
    return 0;
}

int generate_txt_file_from_buffer(uint32_t* data_p, uint32_t data_length, std::string filename)
{
    // Create an ofstream object for writing to a file
    std::ofstream outFile;

    //create/open an output file
    outFile.open(filename);

    // Check if the file was opened successfully
    if (outFile.is_open()) {
        //Indicate start of data
        outFile << "Data: ";
        // insert from data to file
        for (uint32_t i = 0; i < data_length; i++)
        {
            outFile << *(data_p + i) << " ";
        }
        
        outFile << std::endl;
        
        // Close the file
        outFile.close();
        std::cout << "File written successfully." << std::endl;
    } 
    else
    {
        std::cout << "Couldn't open the file." << std::endl;
        return 1;
    }
    
    return 0;
}
