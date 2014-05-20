#include <llmr/renderer/painter.hpp>
#include <llmr/renderer/raster_bucket.hpp>
#include <llmr/map/map.hpp>

using namespace llmr;

void Painter::renderRaster(RasterBucket& bucket, const std::string& layer_name, const Tile::ID& /*id*/) {
    if (pass == Translucent) return;

    auto raster_properties = map.getStyle().computed.rasters;
    auto raster_properties_it = raster_properties.find(layer_name);
    if (raster_properties_it == raster_properties.end()) return;

    const RasterProperties& properties = raster_properties_it->second;
    if (!properties.enabled) return;

    depthMask(false);

    useProgram(rasterShader->program);
    rasterShader->setMatrix(matrix);
    rasterShader->setOpacity(1);
    // rasterShader->setOpacity(properties.opacity * tile_data->raster->opacity);

    glDepthRange(strata + strata_epsilon, 1.0f);
    bucket.drawRaster(*rasterShader, tileStencilBuffer, coveringRasterArray);

    depthMask(true);
}