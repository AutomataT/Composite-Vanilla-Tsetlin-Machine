#include <Arduino.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// If you comment it, change the #defines below accordingly. DO NOT USE y_thresh!
#include "IncludeEncodedSetup_thresh.h"
#include "inference_literals_thresh.h"
#include "IncEncTA_thresh.h"
#include "INC_per_CLASS_thresh.h"

// Uncomment to include HOG
#include "y_hog.h"
#include "IncludeEncodedSetup_hog.h"
#include "inference_literals_hog.h"
#include "IncEncTA_hog.h"
#include "INC_per_CLASS_hog.h"

// Uncomment to include 3x3
#include "y_3x3.h"
#include "IncludeEncodedSetup_3x3.h"
#include "inference_literals_3x3.h"
#include "IncEncTA_3x3.h"
#include "INC_per_CLASS_3x3.h"

// Uncomment to include 4x4
#include "y_4x4.h"
#include "IncludeEncodedSetup_4x4.h"
#include "inference_literals_4x4.h"
#include "IncEncTA_4x4.h"
#include "INC_per_CLASS_4x4.h"

#define TEST_LENGTH_PER32 IncludeEncodedSetup_thresh::TEST_LENGTH_PER32
#define CLASSES IncludeEncodedSetup_thresh::CLASSES
#define NUMBER_OF_TEST_EXAMPLES IncludeEncodedSetup_thresh::NUMBER_OF_TEST_EXAMPLES
#define CLAUSE_POLARITY_BIT IncludeEncodedSetup_thresh::CLAUSE_POLARITY_BIT
#define BIT_DEMARCATING_CLAUSE_CHANGE IncludeEncodedSetup_thresh::BIT_DEMARCATING_CLAUSE_CHANGE
#define INT_VALUE_OF_ENCODING_BITS IncludeEncodedSetup_thresh::INT_VALUE_OF_ENCODING_BITS

unsigned char infered_classes[TEST_LENGTH_PER32*32];

void inference()
{
  // Iterorate through the TA states
  int cur_class_sum[32];
  int class_sum_agg[CLASSES][TEST_LENGTH_PER32*32] = {0};
	int clause_offset=0;
	int prev_clause_change, curr_clause_change, clause_polarity, literal_polarity, classification;
	unsigned int literal_offset, clause_output;
	int max = 0;

  #ifdef INCLUDEENCODEDSETUP_3X3_H
	for(int k = 0; k < TEST_LENGTH_PER32; k++)
	{
		for(int m=0;m<32;m++)
		{
			cur_class_sum[m] = 0;
		}
		clause_offset=0;
		for(int i = 0; i < CLASSES; i++)
		{
			clause_output = INT_MAX;			
			prev_clause_change = 0;
			curr_clause_change = 0;
			clause_polarity = 0;

			max = clause_offset+INC_per_CLASS_3x3[i];
			for(int j = clause_offset; j < max; j++)
			{
				curr_clause_change = IncEncTA_3x3[j]>>BIT_DEMARCATING_CLAUSE_CHANGE;				
				
				if(curr_clause_change != prev_clause_change)
				{
					if(clause_polarity == 0)
					{
						for(int m=0;m<32;m++)
						{	
							cur_class_sum[m] = cur_class_sum[m] + (int)((clause_output>>(31-m))&1);
						}
					}
					else
					{
						for(int m=0;m<32;m++)
						{
							cur_class_sum[m] = cur_class_sum[m] - (int)((clause_output>>(31-m))&1);
						}
					}
					clause_output = INT_MAX;
				}
				clause_polarity = IncEncTA_3x3[j]>>CLAUSE_POLARITY_BIT;
				literal_offset = (IncEncTA_3x3[j]&INT_VALUE_OF_ENCODING_BITS)>>1;
				literal_polarity = IncEncTA_3x3[j]&1;
				prev_clause_change = curr_clause_change;
				clause_output = (literal_polarity == 0)?(clause_output & inference_literals_3x3[(k*IncludeEncodedSetup_3x3::FEATURES)+literal_offset]):(clause_output & (~inference_literals_3x3[(k*IncludeEncodedSetup_3x3::FEATURES)+literal_offset]) );
			}
			clause_offset = clause_offset + INC_per_CLASS_3x3[i];

      for(int m=0;m<32;m++)
      {
        class_sum_agg[i][k*32 + m]+=cur_class_sum[m];
        cur_class_sum[m] = 0;
      }
		}
	}
  #endif

  #ifdef INCLUDEENCODEDSETUP_4X4_H
	for(int k = 0; k < TEST_LENGTH_PER32; k++)
	{
		for(int m=0;m<32;m++)
		{
			cur_class_sum[m] = 0;
		}
		clause_offset=0;
		for(int i = 0; i < CLASSES; i++)
		{
			clause_output = INT_MAX;			
			prev_clause_change = 0;
			curr_clause_change = 0;
			clause_polarity = 0;

			max = clause_offset+INC_per_CLASS_4x4[i];
			for(int j = clause_offset; j < max; j++)
			{
				curr_clause_change = IncEncTA_4x4[j]>>BIT_DEMARCATING_CLAUSE_CHANGE;				
				
				if(curr_clause_change != prev_clause_change)
				{
					if(clause_polarity == 0)
					{
						for(int m=0;m<32;m++)
						{	
							cur_class_sum[m] = cur_class_sum[m] + (int)((clause_output>>(31-m))&1);
						}
					}
					else
					{
						for(int m=0;m<32;m++)
						{
							cur_class_sum[m] = cur_class_sum[m] - (int)((clause_output>>(31-m))&1);
						}
					}
					clause_output = INT_MAX;
				}
				clause_polarity = IncEncTA_4x4[j]>>CLAUSE_POLARITY_BIT;
				literal_offset = (IncEncTA_4x4[j]&INT_VALUE_OF_ENCODING_BITS)>>1;
				literal_polarity = IncEncTA_4x4[j]&1;
				prev_clause_change = curr_clause_change;
				clause_output = (literal_polarity == 0)?(clause_output & inference_literals_4x4[(k*IncludeEncodedSetup_4x4::FEATURES)+literal_offset]):(clause_output & (~inference_literals_4x4[(k*IncludeEncodedSetup_4x4::FEATURES)+literal_offset]) );
			}
			clause_offset = clause_offset + INC_per_CLASS_4x4[i];

      for(int m=0;m<32;m++)
      {
        class_sum_agg[i][k*32 + m]+=cur_class_sum[m];
        cur_class_sum[m] = 0;
      }
		}
	}
  #endif

  #ifdef INCLUDEENCODEDSETUP_HOG_H
	for(int k = 0; k < TEST_LENGTH_PER32; k++)
	{
		for(int m=0;m<32;m++)
		{
			cur_class_sum[m] = 0;
		}
		clause_offset=0;
		for(int i = 0; i < CLASSES; i++)
		{
			clause_output = INT_MAX;			
			prev_clause_change = 0;
			curr_clause_change = 0;
			clause_polarity = 0;

			max = clause_offset+INC_per_CLASS_hog[i];
			for(int j = clause_offset; j < max; j++)
			{
				curr_clause_change = IncEncTA_hog[j]>>BIT_DEMARCATING_CLAUSE_CHANGE;				
				
				if(curr_clause_change != prev_clause_change)
				{
					if(clause_polarity == 0)
					{
						for(int m=0;m<32;m++)
						{	
							cur_class_sum[m] = cur_class_sum[m] + (int)((clause_output>>(31-m))&1);
						}
					}
					else
					{
						for(int m=0;m<32;m++)
						{
							cur_class_sum[m] = cur_class_sum[m] - (int)((clause_output>>(31-m))&1);
						}
					}
					clause_output = INT_MAX;
				}
				clause_polarity = IncEncTA_hog[j]>>CLAUSE_POLARITY_BIT;
				literal_offset = (IncEncTA_hog[j]&INT_VALUE_OF_ENCODING_BITS)>>1;
				literal_polarity = IncEncTA_hog[j]&1;
				prev_clause_change = curr_clause_change;
				clause_output = (literal_polarity == 0)?(clause_output & inference_literals_hog[(k*IncludeEncodedSetup_hog::FEATURES)+literal_offset]):(clause_output & (~inference_literals_hog[(k*IncludeEncodedSetup_hog::FEATURES)+literal_offset]) );
			}
			clause_offset = clause_offset + INC_per_CLASS_hog[i];

      for(int m=0;m<32;m++)
      {
        class_sum_agg[i][k*32 + m]+=cur_class_sum[m];
        cur_class_sum[m] = 0;
      }
		}
	}
  #endif

  #ifdef INCLUDEENCODEDSETUP_THRESH_H
	for(int k = 0; k < TEST_LENGTH_PER32; k++)
	{
		for(int m=0;m<32;m++)
		{
			cur_class_sum[m] = 0;
		}
		clause_offset=0;
		for(int i = 0; i < CLASSES; i++)
		{
			clause_output = INT_MAX;			
			prev_clause_change = 0;
			curr_clause_change = 0;
			clause_polarity = 0;

			max = clause_offset+INC_per_CLASS_thresh[i];
			for(int j = clause_offset; j < max; j++)
			{
				curr_clause_change = IncEncTA_thresh[j]>>BIT_DEMARCATING_CLAUSE_CHANGE;				
				
				if(curr_clause_change != prev_clause_change)
				{
					if(clause_polarity == 0)
					{
						for(int m=0;m<32;m++)
						{	
							cur_class_sum[m] = cur_class_sum[m] + (int)((clause_output>>(31-m))&1);
						}
					}
					else
					{
						for(int m=0;m<32;m++)
						{
							cur_class_sum[m] = cur_class_sum[m] - (int)((clause_output>>(31-m))&1);
						}
					}
					clause_output = INT_MAX;
				}
				clause_polarity = IncEncTA_thresh[j]>>CLAUSE_POLARITY_BIT;
				literal_offset = (IncEncTA_thresh[j]&INT_VALUE_OF_ENCODING_BITS)>>1;
				literal_polarity = IncEncTA_thresh[j]&1;
				prev_clause_change = curr_clause_change;
				clause_output = (literal_polarity == 0)?(clause_output & inference_literals_thresh[(k*IncludeEncodedSetup_thresh::FEATURES)+literal_offset]):(clause_output & (~inference_literals_thresh[(k*IncludeEncodedSetup_thresh::FEATURES)+literal_offset]) );
			}
			clause_offset = clause_offset + INC_per_CLASS_thresh[i];

      for(int m=0;m<32;m++)
      {
        class_sum_agg[i][k*32 + m]+=cur_class_sum[m];
        cur_class_sum[m] = 0;
      }
		}
	}
  #endif

  for(int i=0;i<TEST_LENGTH_PER32*32;i++){
    int max_class_sum = INT_MIN;

    for(int j=0; j<CLASSES; j++){
      if(class_sum_agg[j][i]>max_class_sum){
        max_class_sum = class_sum_agg[j][i];
        classification = j;
      }
    }

    infered_classes[i] = classification;
  }
}

void setup() {
  Serial.begin(115200);
	while (!Serial);
  delay(1000);  // Ensure serial is ready

  Serial.println("*---------------------------------------------------------------------*");
  Serial.println("|\tCOMPOSITE VANILLA TSETLIN MACHINE INFERENCE\t|");
  Serial.println("*---------------------------------------------------------------------*");

  int errors = 0;
  int l = 0, i = 0;

  unsigned long start_time = micros();

  inference();  // Core logic

  unsigned long end_time = micros();

  unsigned long inf_time = end_time - start_time;

  // if ((TEST_LENGTH_PER32 * 32) > NUMBER_OF_TEST_EXAMPLES) {
  //   for (l = 0; l < (TEST_LENGTH_PER32 - 1) * 32; l++) {
  //     if (infered_classes[l] != y_thresh[l]) {
  //       errors += 1;
  //     }
  //   }
  //   i = l;

  //   for (l = ((TEST_LENGTH_PER32 * 32)) - (NUMBER_OF_TEST_EXAMPLES - ((TEST_LENGTH_PER32 - 1) * 32));
  //        l < ((TEST_LENGTH_PER32 * 32) - 1); l++) {
  //     if (infered_classes[l] != y_thresh[i]) {
  //       errors += 1;
  //     }
  //     i++;
  //   }
  // } 
  // else {
  //   for (l = 0; l < (TEST_LENGTH_PER32) * 32; l++) {
  //     if (infered_classes[l] != y_thresh[l]) {
  //       errors += 1;
  //     }
  //   }
  // }

  for (l = 0; l < (TEST_LENGTH_PER32) * 32; l++) {
    if (infered_classes[l] != y_hog[l]) {
      errors += 1;
    }
  }

  float accuracy = 1.0 - (float)errors / NUMBER_OF_TEST_EXAMPLES;
  Serial.println("*-----------------------------------------------*");
  Serial.print("|\tAcc            : ");
  Serial.print(accuracy, 4);
  Serial.println("\t             \t|");
  Serial.println("*-----------------------------------------------*");
  Serial.print("Total erroneous classifications - ");
  Serial.println(errors);
  Serial.print("Inference completed in (mus): ");
  Serial.println(inf_time);
}

void loop() {
  // Optional: rerun inference or sleep
}