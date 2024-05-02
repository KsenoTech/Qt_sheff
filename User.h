#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User() {}

    // Методы установки значений полей
    void setUsername(const QString& username) { m_username = username; }
    void setFullName(const QString& fullName) { m_fullName = fullName; }
    void setRoomNumber(int roomNumber) { m_roomNumber = roomNumber; }
    void setId(int Id) { m_Id = Id; }
    void setRating(double rating) { m_rating = rating; }

    // Методы получения значений полей
    QString username() const { return m_username; }
    QString fullName() const { return m_fullName; }
    int roomNumber() const { return m_roomNumber; }
    int Id() const { return m_Id; }
    double rating() const { return m_rating; }

private:
    QString m_username;
    QString m_fullName;
    int m_roomNumber;
    int m_Id;
    double m_rating;
};

#endif // USER_H
