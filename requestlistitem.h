// В классе RequestListItem.h
#ifndef REQUESTLISTITEM_H
#define REQUESTLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class RequestListItem : public QWidget {
    Q_OBJECT
public:
    RequestListItem(QWidget *parent = nullptr) : QWidget(parent) {
        layout = new QHBoxLayout(this);
        roomLabel = new QLabel(this);
        statusLabel = new QLabel(this);
        descriptionLabel = new QLabel(this);
        photoLabel = new QLabel(this);
        fioLabel = new QLabel(this);
        ratingLabel = new QLabel(this);



        layout->addWidget(descriptionLabel);
        layout->addWidget(statusLabel);
        layout->addWidget(photoLabel);
        layout->addWidget(fioLabel);
        layout->addWidget(roomLabel);
        layout->addWidget(ratingLabel);
    }

    void setRoom(const QString &room) {
        roomLabel->setText(room);
    }

    void setStatus(const QString &status) {
        statusLabel->setText(status);
    }

    void setDescription(const QString &description) {
        descriptionLabel->setText(description);
    }

    void setPhoto(const QPixmap &photo) {
        photoLabel->setPixmap(photo);
    }

    void setFIO(const QString &fio) {
        fioLabel->setText(fio);
    }

    void setRating(const QString &rating) {
        ratingLabel->setText(rating);
    }

private:
    QHBoxLayout *layout;

    QLabel *roomLabel;
    QLabel *statusLabel;
    QLabel *descriptionLabel;
    QLabel *photoLabel;

    QLabel *fioLabel;
    QLabel *ratingLabel;
};

#endif // REQUESTLISTITEM_H
