#include "app.h"

#include "utility/tracer.h"

#if defined(PLATFORM_WINDOWS)
int APIENTRY WinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/,
					 _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
#else
main()
#endif
{
	Tracer::begin("profile.json");

	if (const auto exitCode = App::init(); exitCode != App::ExitCode::success)
		return static_cast<int>(exitCode);

	const auto exitCode = App::run();

	Tracer::end();

	return static_cast<int>(exitCode);
}