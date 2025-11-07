#ifndef QT_TOOLTIP_H
#define QT_TOOLTIP_H

#include <QFrame>

struct TooltipInfo;

class QtTooltip: public QFrame
{
	Q_OBJECT

public:
	QtTooltip(QWidget* parent = nullptr);

	void setTooltipInfo(const TooltipInfo& info);

	void setParentView(QWidget* parentView);

	bool isHovered() const;

public slots:
	void show();
	void hide(bool force = false);

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	void addTitle(const QString& title, int count, const QString& countText);
	void addWidget(QWidget* widget);
	void clearLayout(QLayout* layout);

	QWidget *getParent() const;

	QWidget* m_parentView = nullptr;
	QPoint m_offset;

	bool m_isHovered = false;
};

#endif	  // QT_TOOLTIP_H
