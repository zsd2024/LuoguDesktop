#include <KAboutData>
#include <KIconTheme>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QUrl>
#include <QtQml>

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    // 启用高 DPI 缩放支持，确保在高分辨率屏幕上界面按比例缩放
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // 初始化 KDE 图标主题（使 KIconTheme 可用）
    KIconTheme::initTheme();

    // 创建 QApplication 实例，管理应用的事件循环与全局状态
    QApplication app(argc, argv);

    // -------------------------
    // 国际化域设置
    // -------------------------
    // KLocalizedString::setApplicationDomain 用于指定 i18n/i18nc
    // 在提取翻译时使用的域名（domain）。 使用反向域名（与 QML 模块或应用 ID
    // 对应）可以让翻译字符串更容易归类。
    KLocalizedString::setApplicationDomain("com.github.zsd2024.LuoguDesktop");

    // -------------------------
    // 应用元信息（组织与应用名）
    // -------------------------
    // 这些信息会影响 QSettings 的默认路径、About 对话框显示以及某些平台的元数据。
    QApplication::setOrganizationName(QStringLiteral("zsd2024"));
    QApplication::setOrganizationDomain(QStringLiteral("github.com"));
    QApplication::setApplicationName(QStringLiteral("Luogu Desktop"));

    // -------------------------
    // 应用图标与桌面文件名
    // -------------------------
    // setWindowIcon：设置应用程序的窗口图标（使用图标主题中的名称）
    // setDesktopFileName：设置 .desktop 文件名（不带路径），用于桌面环境识别应用
    QApplication::setWindowIcon(QIcon(QStringLiteral("luogu-desktop")));
    QApplication::setDesktopFileName(QStringLiteral("com.github.zsd2024.LuoguDesktop"));

    // -------------------------
    // Qt / Kirigami 风格设置
    // -------------------------
    // 设置应用的 QWidget 风格（breeze）以及 Qt Quick Controls
    // 的样式（org.kde.desktop） 如果环境变量 QT_QUICK_CONTROLS_STYLE
    // 已被设置，则保留用户设置
    QApplication::setStyle(QStringLiteral("breeze"));
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE"))
    {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }

    // -------------------------
    // AboutData：应用关于信息（用于 About 对话框与翻译）
    // -------------------------
    // KAboutData 的第一个参数通常是内部程序名或组件
    // id（与桌面文件名或可执行名相关） i18nc/i18n 用于国际化字符串，i18nc
    // 提供上下文提示给翻译者
    KAboutData aboutData(
        QStringLiteral("com.github.zsd2024.LuoguDesktop"), // internal program
                                                           // name / component id
        i18nc("@title", "Luogu Desktop"),                  // 显示名称（可翻译）
        QStringLiteral("0.1-dev"),                         // 版本号
        i18n("Unofficial Luogu client"),                   // 简短描述（可翻译）
        KAboutLicense::GPL_V3,                             // 许可证类型
        i18n("Copyright © 2026 Luogu Desktop")             // 版权信息（可翻译）
    );

    // 添加作者信息：姓名、角色、电子邮件、网址
    aboutData.addAuthor(
        i18nc("@info:credit", "zsd2024"),            // 作者姓名（翻译上下文）
        i18nc("@info:credit", "Developer"),          // 作者角色（翻译上下文）
        QStringLiteral("zsd_2024@outlook.com"),      // 联系邮箱（可选）
        QStringLiteral("https://github.com/zsd2024") // 个人或项目网址（可选）
    );

    aboutData.setOrganizationDomain("github.com");
    aboutData.setDesktopFileName(u"com.github.zsd2024.LuoguDesktop"_s);

    // 将 aboutData 设置为全局应用信息，KAboutData::applicationData()
    // 可在程序任意处访问
    KAboutData::setApplicationData(aboutData);

    // -------------------------
    // 在 QML 中注册单例 About 对象
    // -------------------------
    // qmlRegisterSingletonType 将 KAboutData 暴露给 QML，QML 中可通过：
    // import com.github.zsd2024.LuoguDesktop 1.0
    // ...
    // About.someProperty
    // 访问 aboutData 的属性（由 KAboutData 提供）。
    qmlRegisterSingletonType(
        "com.github.zsd2024.LuoguDesktop", // QML 导入名（必须与
                                           // ecm_add_qml_module 注册的 URI 一致）
        1, 0,                              // 版本号（主版本、次版本）
        "About",                           // QML 中的对象名
        [](QQmlEngine *engine, QJSEngine *) -> QJSValue
        {
            // 将 KAboutData::applicationData() 转换为 QML 可用的脚本值并返回
            return engine->toScriptValue(KAboutData::applicationData());
        });

    // -------------------------
    // 创建并配置 QQmlApplicationEngine
    // -------------------------
    // QQmlApplicationEngine 用于加载 QML 界面并创建根对象
    QQmlApplicationEngine engine;

    // 将 KLocalizedContext 注入 QML 上下文，使 QML 中的 i18n/i18nc 能正常工作
    // KLocalizedContext 会把 C++ 的翻译域与 QML 绑定起来
    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));

    // 加载 QML 模块中的 Main.qml
    // loadFromModule 的第一个参数是 QML 模块 URI（与 ecm_add_qml_module 注册的
    // URI 一致） 第二个参数是模块内的主 QML 文件名（不带扩展名）
    engine.loadFromModule("com.github.zsd2024.LuoguDesktop", "Main");

    // 如果没有加载到任何根对象，说明 QML 加载失败，返回错误码
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    // 进入 Qt 事件循环
    return app.exec();
}
