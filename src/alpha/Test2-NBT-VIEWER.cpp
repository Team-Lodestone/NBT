#include <QApplication>
#include <QTreeWidget>
#include <nbt.h>

void printTagsGui(QTreeWidgetItem* parent, nbt::tag_compound& tag, QTreeWidget* treeview) {
    for (auto& [key, value] : tag) {
        QTreeWidgetItem* child = new QTreeWidgetItem(parent);
        child->setText(0, QString::fromStdString(key));
        if (value.type() == nbt::tag_type::compound) {
            printTagsGui(child, value.as<nbt::tag_compound>(), treeview);
        } else if (value.type() == nbt::tag_type::list) {
            for (auto& subValue : value.as<nbt::tag_list>()) {
                QTreeWidgetItem* subChild = new QTreeWidgetItem(child);
                subChild->setText(0, QString::fromStdString(subValue.to_string()));
                if (subValue.type() == nbt::tag_type::compound) {
                    printTagsGui(subChild, subValue.as<nbt::tag_compound>(), treeview);
                }
            }
        } else {
            child->setText(0, QString::fromStdString(value.to_string()));
        }
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QTreeWidget treeview;
    treeview.setHeaderHidden(true);
    treeview.show();

    nbt::NBT nbtFile("SimpleNBT.nbt");
    printTagsGui(nullptr, nbtFile, &treeview);

    return app.exec();
}
