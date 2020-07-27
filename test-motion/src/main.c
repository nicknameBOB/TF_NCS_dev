/*
* Copyright (c) 2012-2014 Wind River Systems, Inc.
*
* SPDX-License-Identifier: Apache-2.0
*/

#include <zephyr.h>
// #include <printk.h>
#include <spi.h>
#include <gpio.h>

#define cs_controller DT_NORDIC_NRF_SPI_SPI_3_CS_GPIOS_CONTROLLER_0
#define cd_pin  DT_NORDIC_NRF_SPI_0_CS_GPIOS_PIN_0

static const struct spi_config spi_cfg = {
	.operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB,
	.frequency = 8000000,
	.slave = 0,
};

struct device * spi_dev;
struct device * cs_gpio;

static void spi_init(void)
{
	const char* const spiName = "SPI_3";
	spi_dev = device_get_binding(spiName);

	if (spi_dev == NULL) {
		printk("Could not get %s device\n", spiName);
		return;
	}
}

void spi_test_send(void)
{
	int err;
	static u8_t tx_buffer[1];
	static u8_t rx_buffer[1];

	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
		.len = sizeof(tx_buffer)
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = sizeof(rx_buffer),
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};

	err = spi_transceive(spi_dev, &spi_cfg, &tx, &rx);
	if (err) {
		printk("SPI error: %d\n", err);
	} else {
		/* Connect MISO to MOSI for loopback */
		printk("TX sent: %x\n", tx_buffer[0]);
		printk("RX recv: %x\n", rx_buffer[0]);
		tx_buffer[0]++;
	}
}

void spi_read_reg(void)
{
  u8_t cmd =      0x0B;
  u8_t reg_addr = 0x02;
  u8_t value = 0x00;
  void *data = &value;
  int length = 1;
	u8_t access[2] = { cmd, reg_addr };

  gpio_pin_write(cs_gpio, cd_pin, 0);

	const struct spi_buf buf[2] = {
		{
			.buf = access,
			.len = 2
		},
		{
			.buf = data,
			.len = length
		}
	};
	struct spi_buf_set tx = {
		.buffers = buf,
	};


	const struct spi_buf_set rx = {
		.buffers = buf,
		.count = 2
	};

	tx.count = 1;

	int spi_result = spi_transceive(spi_dev, &spi_cfg, &tx, &rx);

  printk("SPI result: %d\n",spi_result);
  printk("Value: 0x%02X\n", value);

  gpio_pin_write(cs_gpio, cd_pin, 1);

}

void cs_setup(void)
{

  cs_gpio = device_get_binding(cs_controller);

  if (cs_gpio == NULL) {
    printk("Could not get gpio device\n");
    return;
  }

  /* Set cs pin as output */
  gpio_pin_configure(cs_gpio, cd_pin, GPIO_DIR_OUT);

  gpio_pin_write(cs_gpio, cd_pin, 1);

}

void main(void)
{
	printk("SPIM Example\n");
  cs_setup();
	spi_init();

	while (1) {
		//spi_test_send();
    spi_read_reg();
		k_sleep(1000);
	}
}