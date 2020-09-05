#include "video.h"

MyVideoWidget::MyVideoWidget(QWidget *parent, QtPlayer *player) : VideoRenderWidget(parent) {
    m_player = player;
}

void MyVideoWidget::SetPlayer(QtPlayer *player) {
    m_player = player;
}

void MyVideoWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        VideoRenderWidget::setFocus();
        PlayPause();
    } else {
        VideoRenderWidget::mousePressEvent(event);
    }
}

void MyVideoWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        PlayPause();
    } else {
        VideoRenderWidget::keyPressEvent(event);
    }
}

void MyVideoWidget::PlayPause() {
    if (m_player == nullptr) {
        return;
    }

    if (m_player->Mode() == PLAYBACK_PAUSED || m_player->Mode() == PLAYBACK_STOPPED) {
        m_player->Play();
    } else if (m_player->Mode() == PLAYBACK_PLAY) {
        m_player->Pause();
    }
}
