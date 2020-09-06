#include "video.h"

MyVideoWidget::MyVideoWidget(QWidget *parent, QtPlayer *player, QTimer *timer) : VideoRenderWidget(parent) {
    m_player = player;
    m_timer = timer;
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
    if (m_player == nullptr || m_timer == nullptr) {
        return;
    }

    if (m_player->Mode() == PLAYBACK_PAUSED || m_player->Mode() == PLAYBACK_STOPPED) {
        m_player->Play();
        m_timer->start();
    } else if (m_player->Mode() == PLAYBACK_PLAY) {
        m_player->Pause();
        m_timer->stop();
    }
}

void MyVideoWidget::SetTimer(QTimer *timer) {
    m_timer = timer;
}
