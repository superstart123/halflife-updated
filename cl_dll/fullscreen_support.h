// Fullscreen Support Header
#ifndef FULLSCREEN_SUPPORT_H
#define FULLSCREEN_SUPPORT_H

#include "cbase.h"

// Fullscreen configuration structure
struct FullscreenConfig
{
    int width;
    int height;
    int refresh_rate;
    int color_bits;
    bool enable_vsync;
    bool enable_fullscreen;
    bool enable_borderless;
    bool keep_aspect_ratio;
};

// Fullscreen manager class
class CFullscreenManager
{
public:
    static CFullscreenManager& GetInstance();
    
    // Initialize fullscreen support
    void Initialize();
    
    // Set fullscreen mode
    void SetFullscreen(bool enable);
    
    // Set borderless windowed mode
    void SetBorderlessWindow(bool enable);
    
    // Get current resolution
    void GetResolution(int& width, int& height);
    
    // Set resolution
    void SetResolution(int width, int height);
    
    // Get refresh rate
    int GetRefreshRate() const;
    
    // Set refresh rate
    void SetRefreshRate(int rate);
    
    // Enable/Disable VSync
    void SetVSync(bool enable);
    
    // Maintain aspect ratio
    void MaintainAspectRatio(bool maintain);
    
    // Get fullscreen configuration
    FullscreenConfig GetConfig() const;
    
    // Save configuration to file
    void SaveConfig();
    
    // Load configuration from file
    void LoadConfig();
    
    // Apply configuration
    void ApplyConfig(const FullscreenConfig& config);
    
    // Get available resolutions
    void GetAvailableResolutions(std::vector<std::pair<int, int>>& resolutions);
    
    // Get supported refresh rates
    void GetSupportedRefreshRates(std::vector<int>& rates);

private:
    CFullscreenManager();
    ~CFullscreenManager();
    
    FullscreenConfig m_current_config;
    bool m_is_fullscreen;
    bool m_is_borderless;
    
    // Singleton instance
    static CFullscreenManager* m_instance;
};

// Console commands for fullscreen
void FS_ToggleFullscreen();
void FS_SetResolution(int width, int height);
void FS_SetRefreshRate(int rate);
void FS_SetVSync(bool enable);
void FS_ToggleBorderless();

#endif // FULLSCREEN_SUPPORT_H
