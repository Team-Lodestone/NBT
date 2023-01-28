#include <QApplication>
#include <QTreeWidget>
#include <nbt.h>

// My python nbt gui reader converted to good ol c++ with QT! Please Work!!

void print_tags_gui(QTreeWidgetItem* parent, NBT::Tag* tag, QTreeWidget* treeview) {
    //A function to recursively add all the tags in an NBT file to a treeview.
    if (tag->getType() == NBT::Tag::Type::TAG_COMPOUND) {
        NBT::TagCompound* tagCompound = dynamic_cast<NBT::TagCompound*>(tag);
        for (auto& key : tagCompound->getKeys()) {
            QTreeWidgetItem* child = new QTreeWidgetItem(parent);
            child->setText(0, QString::fromStdString(key));
            print_tags_gui(child, tagCompound->get(key), treeview);
        }
    } else if (tag->getType() == NBT::Tag::Type::TAG_LIST) {
        NBT::TagList* tagList = dynamic_cast<NBT::TagList*>(tag);
        for (auto& item : tagList->getList()) {
            QTreeWidgetItem* child = new QTreeWidgetItem(parent);
            child->setText(0, QString::fromStdString(item->toString()));
            print_tags_gui(child, item, treeview);
        }
    } else {
        QTreeWidgetItem* child = new QTreeWidgetItem(parent);
        child->setText(0, QString::fromStdString(tag->toString()));
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QTreeWidget treeview;
    treeview.show();

    NBT::File file;
    file.read("SimpleNBT.nbt");
    print_tags_gui(nullptr, &file.getRootTag(), &treeview);

    return app.exec();
}
