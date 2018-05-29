#include "effects/effects.h"

#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>

#include "ui/collapsiblewidget.h"

VolumeEffect::VolumeEffect(Clip* c) : Effect(c) {
	container = new CollapsibleWidget();
	container->setText(audio_effect_names[AUDIO_VOLUME_EFFECT]);

	ui = new QWidget();

	QGridLayout* ui_layout = new QGridLayout();

	ui_layout->addWidget(new QLabel("Volume:"), 0, 0);
	volume_val = new QSpinBox();
	volume_val->setMinimum(0);
	volume_val->setMaximum(100);
	ui_layout->addWidget(volume_val, 0, 1);

	ui->setLayout(ui_layout);

	container->setContents(ui);

	// set defaults
	volume_val->setValue(100);
}

void VolumeEffect::process_audio(uint8_t *samples, int nb_bytes) {
	for (int i=0;i<nb_bytes;i+=2) {
		int16_t full_sample = (int16_t) ((samples[i+1] << 8) | samples[i]);
		full_sample *= volume_val->value()*0.01;
		samples[i+1] = (uint8_t) (full_sample >> 8);
		samples[i] = (uint8_t) full_sample;
	}
}
