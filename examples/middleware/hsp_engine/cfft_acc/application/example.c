/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "example.h"
#include "mx_hsp_engine_app.h"
#include "hsp_bram.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define INPUT_SIGNAL_SAMPLES_SIZE  512U
#define INPUT_COMPLEX_SAMPLES_SIZE  (INPUT_SIGNAL_SAMPLES_SIZE / 2U)
#define CFFT_RESULT_SIZE  INPUT_COMPLEX_SAMPLES_SIZE
#define NB_DOMINANT_FREQUENCY_MAX 5U    /* Max number of dominant frequencies to be detected */
#define SAMPLING_FREQUENCY        256U /* Sampling frequency in Hz */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* BRAM Resources Static Allocation ------------------------------------------*/
float32_t rms_kpi __attribute__((section(".HSP_DATA_BRAM"))) = { 10.0f };

/* BRAM Resources Dynamic Allocation -----------------------------------------*/
float32_t *p_buff_in;  /* BRAM Input Buffer */
float32_t *p_cfft_magnitude;  /* BRAM CFFT Magnitude Output Buffer */

/** The "input_signal_samples" table below is precomputed offline and embedded as static example data.
  * Signal: combines 2 signals:
  *   - 13Hz with phase -PI / 3
  *   - 34Hz with phase  PI / 4
  * N = 256 complex samples, sampling frequency fs = 256Hz
  * CFFT index k related to f(k) = k * fs / N
  */
static const float32_t input_signal_samples[INPUT_SIGNAL_SAMPLES_SIZE] =
{
  2147483647,  0,  2147483647,  2062718848,  996922304,  2147483647,
  -859297984,  2147483647, -1669853184,  1019556352, -1140918528, -339172352,
  116955784, -639648384,  1016462400,  266905168,  734119040,  1656961024,
  -725319872,  2147483647, -2147483648,  1820151040, -2147483648, -19212132,
  -2147483648, -2146722432, -1119330304, -2147483648,  997092032, -2147483648,
  2147483647, -1604537472,  2093764736,  129688920,  876502592,  1006631360,
  -370656608,  589530112, -657527296, -644462720,  302922048, -1638224256,
  1896071296, -1473951872,  2147483647, -2803472,  2147483647,  2031413760,
  1115073664,  2147483647, -1102179968,  2147483647, -2147483648,  1982293120,
  -2147483648, -15311099, -1744691328, -1397598592, -201852816, -1467878528,
  650174656, -431061120,  248451216,  766288768, -1062950144,  1084533504,
  -2147483648,  99432664, -2147483648, -1697458432, -1022257984, -2147483648,
  1127575040, -2147483648,  2147483647, -2140571136,  2147483647, -19335702,
  2147483647,  1757289728,  652547840,  2147483647, -714002176,  1464408960,
  -884398208,  101509512,  87378400, -708850880,  1340421120, -289567360,
  1794878976,  1151611776,  887208256,  2147483647, -1032893504,  2147483647,
  -2147483648,  2093764736, -2147483648,  5213060, -2147483648, -2025284480,
  -954915136, -2147483648,  831922944, -2147483648,  1542118144, -880714752,
  938556352,  392483648, -322532544,  573165120, -1148861568, -428090752,
  -756229504, -1843007360,  791983744, -2147483648,  2147483647, -1878849536,
  2147483647,  17413842,  2147483647,  2144831616,  1105968384,  2147483647,
  -970623360,  2147483647, -2147483648,  1503238528, -1913700352, -163813056,
  -684987968, -929730368,  495850016, -413677440,  667710720,  855320384,
  -398758560,  1805066880, -2038746880,  1548587904, -2147483648, -6672275,
  -2147483648, -2071703552, -1124398336, -2147483648,  1086077184, -2147483648,
  2147483647, -1924306688,  2147483647,  31058874,  1585117696,  1320011392,
  95839176,  1294770176, -645731456,  215957120, -129688920, -943235776,
  1243637504, -1163022336,  2147483647, -72978488,  2147483647,  1781814400,
  1045734848,  2147483647, -1130970368,  2147483647, -2147483648,  2126143104,
  -2147483648,  17478114, -2147483648, -1690748928, -573765952, -2125314688,
  696102144, -1266098944,  753242048,  67483304, -289668480,  780482304,
  -1536251008,  243767696, -1916572032, -1276478080, -915307328, -2147483648,
  1062950144, -2147483648,  2147483647, -2118034944,  2147483647, -10080700,
  2147483647,  1981871488,  906784768,  2147483647, -805414208,  2147483647,
  -1412296448,  735529984, -734155136, -449368736,  528539104, -509661952,
  1281006976,  584482880,  780085184,  2021830144, -852479360,  2147483647,
  -2147483648,  1932910592, -2147483648, -14260137, -2147483648, -2135168256,
  -1087246592, -2147483648,  943235776, -2147483648,  2034311808, -1393793408,
  1727606400,  201838928,  489127744,  854223936, -623548288,  239433552,
  -680615488, -1062804032,  489111040, -1967671936,  2147483647, -1621017600,
  2147483647,  13348180,  2147483647,  2103240320,  1129807360,  2147483647,
  -1067135936,  2147483647, -2147483648,  1857462912, -2147483648, -50229504,
  -1417902720, -1241664768,  14794505, -1119641984,  644245120,  0,
  14794505,  1119641984, -1417902720,  1241664768, -2147483648,  50229504,
  -2147483648, -1857462912, -1067135936, -2147483648,  1129807360, -2147483648,
  2147483647, -2103240320,  2147483647, -13348180,  2147483647,  1621017600,
  489111040,  1967671936, -680615488,  1062804032, -623548288, -239433552,
  489127744, -854223936,  1727606400, -201838928,  2034311808,  1393793408,
  943235776,  2147483647, -1087246592,  2147483647, -2147483648,  2135168256,
  -2147483648,  14260137, -2147483648, -1932910592, -852479360, -2147483648,
  780085184, -2021830144,  1281006976, -584482880,  528539104,  509661952,
  -734155136,  449368736, -1412296448, -735529984, -805414208, -2147483648,
  906784768, -2147483648,  2147483647, -1981871488,  2147483647,  10080700,
  2147483647,  2118034944,  1062950144,  2147483647, -915307328,  2147483647,
  -1916572032,  1276478080, -1536251008, -243767696, -289668480, -780482304,
  753242048, -67483304,  696102144,  1266098944, -573765952,  2125314688,
  -2147483648,  1690748928, -2147483648, -17478114, -2147483648, -2126143104,
  -1130970368, -2147483648,  1045734848, -2147483648,  2147483647, -1781814400,
  2147483647,  72978488,  1243637504,  1163022336, -129688920,  943235776,
  -645731456, -215957120,  95839176, -1294770176,  1585117696, -1320011392,
  2147483647, -31058874,  2147483647,  1924306688,  1086077184,  2147483647,
  -1124398336,  2147483647, -2147483648,  2071703552, -2147483648,  6672275,
  -2038746880, -1548587904, -398758560, -1805066880,  667710720, -855320384,
  495850016,  413677440, -684987968,  929730368, -1913700352,  163813056,
  -2147483648, -1503238528, -970623360, -2147483648,  1105968384, -2147483648,
  2147483647, -2144831616,  2147483647, -17413842,  2147483647,  1878849536,
  791983744,  2147483647, -756229504,  1843007360, -1148861568,  428090752,
  -322532544, -573165120,  938556352, -392483648,  1542118144,  880714752,
  831922944,  2147483647, -954915136,  2147483647, -2147483648,  2025284480,
  -2147483648, -5213060, -2147483648, -2093764736, -1032893504, -2147483648,
  887208256, -2147483648,  1794878976, -1151611776,  1340421120,  289567360,
  87378400,  708850880, -884398208, -101509512, -714002176, -1464408960,
  652547840, -2147483648,  2147483647, -1757289728,  2147483647,  19335702,
  2147483647,  2140571136,  1127575040,  2147483647, -1022257984,  2147483647,
  -2147483648,  1697458432, -2147483648, -99432664, -1062950144, -1084533504,
  248451216, -766288768,  650174656,  431061120, -201852816,  1467878528,
  -1744691328,  1397598592, -2147483648,  15311099, -2147483648, -1982293120,
  -1102179968, -2147483648,  1115073664, -2147483648,  2147483647, -2031413760,
  2147483647,  2803472,  1896071296,  1473951872,  302922048,  1638224256,
  -657527296,  644462720, -370656608, -589530112,  876502592, -1006631360,
  2093764736, -129688920,  2147483647,  1604537472,  997092032,  2147483647,
  -1119330304,  2147483647, -2147483648,  2146722432, -2147483648,  19212132,
  -2147483648, -1820151040, -725319872, -2147483648,  734119040, -1656961024,
  1016462400, -266905168,  116955784,  639648384, -1140918528,  339172352,
  -1669853184, -1019556352, -859297984, -2147483648,  996922304, -2147483648,
  2147483647, -2062718848
};

/* Private functions prototype -----------------------------------------------*/

/** ########## Step 1 ##########
  * The applicative code initializes the HSP instance and the MW HSP Engine.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /* Initialize the Middleware HSP Engine */
  if (mx_hsp_engine_init_hsp1() == 0U)
  {
    PRINTF("[INFO] Step 1: MW HSP Engine initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  hsp_engine_context_t *p_mw_hsp_ctxt = mx_hsp_engine_get_context_hsp1();
  uint32_t dominant_frequencies[NB_DOMINANT_FREQUENCY_MAX];
  uint32_t idx_fq = 0U;
  uint32_t nb_dominant_fq;

  /** ########## Step 2 ##########
    * Transfers the samples into the HSP BRAMAB buffers.
    * The calls of barrier (__DSB & __DMB) are mandatory to guarantee that data are well copied when
    * starting the HSP Process.
    */
  /* Load input samples into "p_buff_in" buffer */
  HSP_MEMCPY(p_buff_in, input_signal_samples, INPUT_SIGNAL_SAMPLES_SIZE * sizeof(float32_t));
  __DSB();

  PRINTF("[INFO] Step 2: Samples loaded into HSP BRAMAB buffers.\n");

  /** ########## Step 3 ##########
    * Converts the input samples from Q1.31 to Float32 format and executes the CFFT by using the Direct Command.
    * The results are stored in the "p_buff_in" buffer (stored in HSP BRAMAB memory region) as complex values.
    * Then, computes the magnitude of CFFT to retrieve the real values.
    */

  /* ------Convert the Q1.31 values to Float 32 ------ */
  HSP_ACC_VectQ312F(p_mw_hsp_ctxt, (int32_t *)p_buff_in, p_buff_in, INPUT_SIGNAL_SAMPLES_SIZE);
  __DSB();

  /* ----- Execute the CFFT ----- */
  HSP_ACC_Fft_f32(p_mw_hsp_ctxt, p_buff_in, HSP_LOG2NBP_256, 0U, 1U);
  __DSB();

  /* Compute the magnitude of CFFT results */
  HSP_ACC_CmplxMag_f32(p_mw_hsp_ctxt, p_buff_in, p_cfft_magnitude, CFFT_RESULT_SIZE);
  __DSB();

  PRINTF("[INFO] Step 3: Q1.31 samples converted in Float 32-bit, CFFT executed and magnitude computed.\n");

  /** ########## Step 4 ##########
    * Extract the dominant frequencies from the CFFT magnitude results
    */

  /* Calculate the difference between the reference output signal and the FFT result (complex part) */
  for (uint32_t idx = 0U; idx < CFFT_RESULT_SIZE; idx++)
  {
    float b = p_cfft_magnitude[idx];
    if (b > 50.0f)
    {
      /* Retrieve the dominant Frequency related to the CFFT index */
      /* f(k) = k * fs / N                                        */
      dominant_frequencies[idx_fq] = idx * SAMPLING_FREQUENCY / CFFT_RESULT_SIZE;
      idx_fq++;
      if (idx_fq >= NB_DOMINANT_FREQUENCY_MAX)
      {
        break;
      }
    }
  }

  nb_dominant_fq = idx_fq;

  /* Check Expected Dominant Frequencies */
  if (nb_dominant_fq != 2U)
  {
    goto _app_process_exit;
  }

  if ((dominant_frequencies[0U] != 13U) || (dominant_frequencies[1U] != 34U))
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 4: CFFT process OK.\n");
  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** ########## Step 5 ##########
  * De-initializes the Middleware HSP Engine and then the HSP instance.
  */
app_status_t app_deinit(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  PRINTF("[INFO] Step 5: de-init.\n");

  /** De-initialize the HSP Engine middleware context attached to the HSP1 instance. */
  mx_hsp_engine_deinit_hsp1();

  /** De-initialize the HSP1 instance. */
  mx_hsp_deinit();

  return_status = EXEC_STATUS_OK;

  return return_status;
} /* end app_deinit */


/**
  * brief: Allocate resources in HSP BRAMAB.
  * param: hmw  Pointer to a hsp_engine_context_t.
  * return: error value (0U - no error)
  * note: Override the MW HSP Engine weak function to allocate BRAM resources at MW Init.
  */
uint32_t HSP_BRAM_AllocateHook(hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;

  p_buff_in = (float32_t *)HSP_BRAM_Malloc(hmw, INPUT_SIGNAL_SAMPLES_SIZE, HSP_BRAM_ALLOCATION_DEFAULT);
  if (p_buff_in == NULL) { error++; }

  p_cfft_magnitude = (float32_t *)HSP_BRAM_Malloc(hmw, CFFT_RESULT_SIZE, HSP_BRAM_ALLOCATION_DEFAULT);
  if (p_cfft_magnitude == NULL) { error++; }

  return error;
}
